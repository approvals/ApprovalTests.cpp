import os

from scripts.utilities import write_file


def get_all_files(directory):
    all_files = []
    abs = os.path.abspath(directory)
    relative = os.path.split(abs)[1]

    for root, directories, files in os.walk(directory):
        for file in files:
            if file.endswith('.h'):
                file_text = os.path.join(root, file)
                file_text = file_text.replace('./', relative + '/')
                all_files.append(file_text)

    return all_files


class SingleHeaderFile(object):
    @staticmethod
    def create(directory):

        # 	public static List<File> getAllFiles(String directory) {
        # 		FileFilter filter = p -> p.getName().endsWith(".h") || p.getName().endsWith(".cpp");
        # 		File[] list = FileUtils.getRecursiveFileList(new File(directory), filter);
        # 		Arrays.sort(list);
        # 		return Arrays.asList(list);
        # 	}
        files = get_all_files(directory)
        print(files)
        output_file = os.path.abspath('ApprovalTests.hpp')
        includes = '\n'.join(map(lambda f: f'#include "{f}"', files))
        output = f'''
#ifndef APPROVALTESTS_CPP_APPROVALS_HPP
#define APPROVALTESTS_CPP_APPROVALS_HPP

// Created with:
//   cd ApprovalTests.cpp
//   ./scripts/create_simulated_single_header.sh

{includes}

#endif // APPROVALTESTS_CPP_APPROVALS_HPP

'''
        write_file(output_file, output)
        return output_file
