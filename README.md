# 🫧 Pawn Shell API
Execute commands in Windows or Linux directly from your Pawn code.

# ⭐ Usage Example
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

# 📜 Natives
```pawn
native ShellExec(const command[], const callback[] = "");
```
