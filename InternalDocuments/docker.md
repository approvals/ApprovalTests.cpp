# Debugging CI failures locally with Docker

The Linux CI jobs run on Ubuntu, so a failure that doesn't happen on macOS can usually be reproduced in an Ubuntu container.
Windows, MinGW and Cygwin jobs can't be reproduced this way; use the CI logs for those.

## Get the failure from CI

```bash
gh run list --limit 10
gh run view <run-id> --log-failed
```

If `gh run view` fails (for example with HTTP 502 during a GitHub outage), fetch a single job's log through the API:

```bash
gh api "repos/approvals/ApprovalTests.cpp/actions/runs/<run-id>/jobs" --jq '.jobs[] | "\(.id) \(.conclusion) \(.name)"'
gh api repos/approvals/ApprovalTests.cpp/actions/jobs/<job-id>/logs > job.log
```

To find when a build started failing, look for the last green run and list the commits after it:

```bash
gh run list --workflow build --limit 60 --json conclusion,createdAt,headSha --jq '.[] | "\(.createdAt[:10]) \(.conclusion) \(.headSha[:8])"'
git log --oneline <last-green-sha>..<first-red-sha>
```

## Build an image with the tools

Docker Desktop must be running. Build the image once:

```bash
docker build -t approvaltests-linux - <<'EOF'
FROM ubuntu:24.04
RUN apt-get update -qq && apt-get install -y -qq g++ clang cmake make ninja-build python3 gdb git libboost-all-dev && rm -rf /var/lib/apt/lists/*
EOF
```

## Build and test inside the container

From the repository root:

```bash
docker run --rm -v "$PWD":/ApprovalTests.cpp approvaltests-linux bash -c '
cmake -S /ApprovalTests.cpp -B /build -DCMAKE_BUILD_TYPE=Debug &&
cmake --build /build -j8 &&
cd /build && ctest --output-on-failure'
```

1. Build in `/build`, inside the container, so the build doesn't mix with your macOS build directories.
1. Mount the source at `/ApprovalTests.cpp`. Some tests look for files under a directory with that name.
1. Mount the source writable. Approval tests write `.received` files next to the source, and fail with "Unable to write file" on a read-only mount.
1. To build only part of the repo, point `-S` at that directory. For example, `-S /ApprovalTests.cpp/examples/doctest_multiple_shared_libraries`.
1. To match a compiler from the CI matrix, set `CXX`, for example `CXX=clang++ cmake ...`.

## Get a backtrace for a crash

```bash
docker run --rm -v "$PWD":/ApprovalTests.cpp approvaltests-linux bash -c '
cmake -S /ApprovalTests.cpp -B /build -DCMAKE_BUILD_TYPE=Debug && cmake --build /build -j8 &&
gdb -batch -ex run -ex bt --args /build/<path-to-test-executable> <arguments>'
```

`ctest --verbose` prints each test's command line, which gives the executable and its arguments.

## Differences from CI

1. On Apple Silicon the container runs arm64, while CI runs x86-64. Add `--platform linux/amd64` to `docker build` and `docker run` if a failure only happens on x86-64. It runs much slower.
1. CI installs specific compiler versions (see `.github/workflows/github_actions_build.yml`). Ubuntu 24.04's default `g++` and `clang++` are usually close enough.
