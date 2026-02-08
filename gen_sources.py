# Generate sources for CMake
import os

SRC_DIR = "src"
OUT_FILE = "sources.cmake"
WEB_PREFIX = "WEB_"
NATIVE_PREFIX = "NATIVE_"


def generate_set(sources, label) -> str:
    concat_files = ""
    for i, filepath in enumerate(sources):
        if i != 0:
            concat_files += "\n"
        concat_files += f"  {filepath}"
    result = f"""set({label}
{concat_files}
)"""
    return result


def gen_sources():
    src_files = []
    web_specific_src_files = []
    native_specific_src_files = []
    for root, dirs, files in os.walk("src"):
        for file in files:
            if file.endswith(".cpp"):
                filepath = os.path.join(root, file).replace("\\", "/")
                if file.startswith(WEB_PREFIX):
                    web_specific_src_files += [filepath]
                elif file.startswith(NATIVE_PREFIX):
                    native_specific_src_files += [filepath]
                else:
                    src_files += [filepath]

    src_files_str = generate_set(src_files, "AB_ENGINE_SOURCES")

    native_files_str = generate_set(
        native_specific_src_files, "AB_ENGINE_SOURCES_NATIVE"
    )

    web_specific_src_files = generate_set(
        web_specific_src_files, "AB_ENGINE_SOURCES_WEB"
    )

    file_content = f"""# Auto-generated code, do not edit
{src_files_str}
{native_files_str}
{web_specific_src_files}
"""

    with open(OUT_FILE, "w") as output:
        output.write(file_content)
