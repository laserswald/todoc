// argparse.h

/// Argument list.
struct arglist
{
	char* argname;
	int required;
	struct arglist *next;
};

ar