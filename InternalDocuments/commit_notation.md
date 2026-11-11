# Arlo's Git notation

```
<risk> <intention> <description>
```

| code | intention |
| - | - |
| F | feature |
| B | bugfix |
| r | refactoring |
| t | test-only |
| e | development environment |
| d | documentation   |

| code | risk |
| - | - |
| . | We are completely certain that it can't break production |
| - | **Whole system** is verified with comprehensive (unit) testing, before and after this change |
| ! | **This behavior change** is verified with automated tests |
| @ | No verification |

`***` for probably-broken checkpoint

`e` (development environment) changes are always `.` — they can't possibly break production, regardless of how much testing was done.

## Examples

```
. d Update TODO
. t Add test for such-and-such
- r extract function
! F add custom date format scrubbers
```

