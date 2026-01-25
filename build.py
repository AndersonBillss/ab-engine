from subprocess import run
import sys

BUILD_DIR = "build"
ENGINE_OUT = f"{BUILD_DIR}/engine"
ENGINE_WEB_OUT = f"{BUILD_DIR}/web-engine"

DAWN_SRC = "third_party/dawn"
DAWN_OUT_DEBUG = f"{BUILD_DIR}/dawn/debug"
DAWN_INSTALL_DEBUG = f"{BUILD_DIR}/_install/dawn/debug"


def cmd(args, *, working_directory=None):
    print(">>", " ".join(args))
    run(args, check=True, cwd=working_directory)


# Native engine build commands
def build_engine_debug():
    cmd(
        [
            "cmake",
            "-S",
            ".",
            "-B",
            ENGINE_OUT,
            "-G",
            "Ninja",
            "-DCMAKE_C_COMPILER=cl",
            "-DCMAKE_CXX_COMPILER=cl",
            "-DCMAKE_EXPORT_COMPILE_COMMANDS=ON",
        ]
    )
    cmd(["cmake", "--build", ENGINE_OUT])


def run_engine_debug():
    build_engine_debug()
    cmd(["build/engine/ab_engine.exe"])


# Dawn build commands
def dawn_deps():
    cmd(
        [sys.executable, "tools/fetch_dawn_dependencies.py"], working_directory=DAWN_SRC
    )


def dawn_debug_configure():
    cmd(
        [
            "cmake",
            "-S",
            DAWN_SRC,
            "-B",
            DAWN_OUT_DEBUG,
            "-G",
            "Ninja",
            "-DCMAKE_C_COMPILER=cl",
            "-DCMAKE_CXX_COMPILER=cl",
            "-DCMAKE_BUILD_TYPE=Debug",
            "-DDAWN_ENABLE_INSTALL=ON",
        ]
    )


def dawn_debug_build():
    dawn_debug_configure()
    cmd(["cmake", "--build", DAWN_OUT_DEBUG])
    cmd(["cmake", "--install", DAWN_OUT_DEBUG, "--prefix", DAWN_INSTALL_DEBUG])


def dawn_debug_setup():
    dawn_deps()
    dawn_debug_build()


COMMANDS = {
    "build-engine-debug": build_engine_debug,
    "run-engine-debug": run_engine_debug,
    "dawn-debug-setup": dawn_debug_setup,
}


def execute_build(build_command):
    if build_command not in COMMANDS:
        print(f"Unknown command: '{build_command}'")
    else:
        build_fn = COMMANDS[sys.argv[1]]
        print(build_command)
        build_fn()


if len(sys.argv) == 1:
    print("Available build commands:")
    for key in COMMANDS:
        print(f"  {key}")
elif len(sys.argv) == 2:
    execute_build(sys.argv[1])
else:
    print("Must provide two arguments")
