
#if defined _shellapi_function
	#endinput
#endif
#define _shellapi_function

// Natives
native ShellExec(const command[], const callback[] = "");
native ShellExecAwait(const command[], const callback[] = "");
