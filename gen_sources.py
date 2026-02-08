# Generate sources for CMake
import os

SRC_DIR = "src"
OUT_FILE = "sources.cmake"


def gen_sources():
    src_files = []
    for root, dirs, files in os.walk("src"):
        for file in files:
            if file.endswith(".cpp"):
                src_files += [os.path.join(root, file)]

    concat_files = ""
    for i, filepath in enumerate(src_files):
        if i != 0:
            concat_files += "\n"
        concat_files += f"  {filepath}"

    file_content = f"""# Auto-generated code, do not edit
set(AB_ENGINE_SOURCES
{concat_files}
)
"""

    with open(OUT_FILE, "w") as output:
        output.write(file_content)
