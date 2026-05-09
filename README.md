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

# 📜 Natives
```pawn
native ShellExec(const command[], const callback[] = "");
```
