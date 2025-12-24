import subprocess
import json
from pathlib import Path

def item_in_array(item, array):
    result = False
    for _item in array:
        if _item == item:
            result = True
        else:
            continue
    return result

def get_command(file_path, root_path):
    relative_path = file_path.replace(root_path, ".")
    return  f"gcc -c {relative_path} -o " + \
            f"{relative_path
                .replace('Source/', 'Build/obj/')
                .replace('.c', '.o')}" + \
            f" -IInclude -Werror -Wall"

def get_files(path):
    result = []
    for line in str(subprocess.run(f"find {path} -type f -name '*.c'",
                               capture_output=True,
                               text=True, check=True, shell=True).stdout
                ).split("\n"):
        current_config = {
            'directory': path,
            'command': get_command(line, path),
            'file': line.replace(path + '/', "")
        }
        result.append(current_config)
    del result[-1]
    return result

def main():
    NoneScript_path = str(Path(__file__).parent.parent)
    compiledb = get_files(NoneScript_path)
    try:
        with open(f'{NoneScript_path}/compile_commands.json', 'w') as file:
            json.dump(compiledb, file, indent=4)
    except Exception as error:
        print(f"{error}")
        exit(1)


if __name__ == '__main__':
    main()
