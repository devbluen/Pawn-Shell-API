# 🫧 Pawn Shell API
Execute commands in Windows or Linux directly from your Pawn code.

# 🪅 Usage Example
Windows
```pawn
forward OnShellCalc(result, const output[]);
public OnShellCalc(result, const output[]) {
  print(output);
  printf("Result Response -> %d", result);
}

ShellExec("calc.exe", "OnShellCalc");      // Open calculator
```

Linux
```pawn
forward OnShellUpTime(result, const output[]);
public OnShellUpTime(result, const output[]) {
  print(output);
  printf("Result Response -> %d", result);
}

ShellExec("uptime -p", "OnShellUpTime");
```

# ⚙️ How install?
1. Download the files in the releases section.
2. Place the `.dll` or `.so` file in the `components` folder within your project.
3. Place the `.inc` file inside `qawno/include`
4. Include the `#include <ShellApi>` tag in your main `.pwn` file.

# 📜 Natives
```pawn
native ShellExec(const command[], const callback[] = "");
native ShellExecAwait(const command[], const callback[] = "");
```

# 🍪 Development
`git clone --recursive https://github.com/devbluen/Pawn-Shell-API.git`

Windows Building
```ps1
mkdir build; 
cd build;
cmake -DCMAKE_BUILD_TYPE=Release .. -G "Visual Studio 17 2022" -A Win32 -T v142
cmake --build . --config Release
```

Linux Building
```ps1
mkdir build 
cd build 
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_C_FLAGS=-m32 -DCMAKE_CXX_FLAGS=-m32
```
## Releasing a new version

The version lives only in the git tag; CMake and the plugin read it from there.

- **From GitHub:** go to *Actions → Build → Run workflow* and pick `patch`, `minor` or `major`, or type a version such as `1.2.0`. The workflow works out the next version, builds Windows and Linux, creates the `vX.Y.Z` tag and publishes the release with both files attached.
- **From the terminal:** `git tag v1.2.0 && git push origin v1.2.0`

A normal push to a branch only builds the plugin. Its artifacts are named `X.Y.Z-dev.<sha>`.
