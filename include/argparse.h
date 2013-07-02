// argparse.h

/// Argument list.
struct arglist
{
	char argname;
	char option;
	int required;
	struct arglist next;
};
/// Read the arguments from argc and argv using the expression arge
struct arglist read_args(int argc, char argv, char* arge);
