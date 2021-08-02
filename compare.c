_Bool compare(char s[], char sh[])
{ /* check if two strings are identical */
	int i,j;

	for(i=0;(s[i] == ' '|| s[i] == '\t') && s[i];i++)
		{}
	for(j=0;(sh[j] == ' '|| sh[j] == '\t') && s[j];j++)
		{}
	while(s[i++] == sh[j++])
		{}
	return (!sh[j]); //1 if we've reached the null terminator, 0 otherwise
}

int alt_strncmp(char *cs,char *ct,int n)
{ /* compare at most n characters of string cs to string ct; return <0 if
     cs<ct, 0 if cs==ct, or >0 if cs>ct. */
	
	for(;*cs == ' ' || *cs == '\t';cs++)  {}
	for(;*ct == ' ' || *ct == '\t';ct++)  {}
	for (;0 <= n-- && *cs == *ct && *ct;cs++,ct++)	   {}
	if (!*cs)
		return 0;
	return *cs-*ct;
}
