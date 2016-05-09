/*
 *	main() -- possibly run C preprocessor before yyparse()
 */
 
#include <unistd.h>
#include <sys/wait.h>


#include <stdio.h>
#include <string.h>


#ifdef	HAVE_CONFIG
	#include "config.h"
#else
	#define CPP	"/bin/cpp"
	#define VASM	"../vasm/vasm"
#endif



#define PROG 	"vcc"
#define CPP_OPT	"CDEIUP"
#define VCC_OPT "alopst"

#define	kMaxFilenameLen		32
#define kDefaultFilename  	"v.asm"
#define kTempFilename		"v.tmp"


/* Global variables */

/* Files produced by the compiler */
FILE	*temp;
FILE	*assembly;

extern 	FILE *yyerfp;
char	*filename;



/*
 *	Options contains many settings controlling the type
 *	of output and behavior of the compiler.
 */
typedef struct
{
	bool runCpp;
	char cppOptions[7];
	
	char outputFile[kMaxFilenameLen];
	char inputFile[kMaxFilenameLen];
	
	bool compile;
	bool link;
	bool assemble;
	bool clobberTmp;
	bool clobberAsm;
} Options;


/* Function prototypes */
static void usage(const char *progName);
static int cpp(char *);
static Options *parse_cmdline(int argc, char **argv);
static void ShowOptions(const Options *o);


/* External functions */
int link_functions(FILE *in, FILE *out);


void usage(const char *name)
{
	fputs("usage: ", stderr);
	fputs(name, stderr);
	fputs(" [C preprocessor options] [-alpst] [-o filename] source\n", stderr);
	exit(1);
}



int main(int argc, char **argv)
{
	Options *clopt;
	int	status, errors;
	
	yyerfp = stdout;
	clopt = parse_cmdline(argc, argv);
	
	if (strlen(clopt->outputFile) == 0)
	{
		strcpy(clopt->outputFile, kDefaultFilename);
	}
					
	
	if (!freopen(clopt->inputFile, "r", stdin))
	{
		usage(argv[0]);
		exit(1);
	}
	
	/* Run the preprocessor */
	if (clopt->runCpp && cpp(clopt->cppOptions))
	{
		perror("C preprocessor");
		exit(1);
	}
	
	/* Run the compiler */
	if (clopt->compile)
	{
		temp = fopen(kTempFilename, "w");
		if (!temp)
			fprintf(stderr, "Weird file error opening %s\n", kTempFilename);
		errors = yyparse();
		fclose(temp);
		if (errors) exit(0);
	}
	
	/* Run the linker */
	if (clopt->link)
	{
		temp = fopen(kTempFilename, "r");
		assembly = fopen(clopt->outputFile, "w");
		if (!assembly) 
			fprintf(stderr, "Weird file error opening %s\n", clopt->outputFile);
		link_functions(temp, assembly);
		fclose(assembly);
		fclose(temp);
	}
	
	/* Perhaps a breach of etiquette, but what the hell */
	all_program();
	
	
	/* Clean up the temp file */
	if (clopt->clobberTmp && remove(kTempFilename))
	{
		fprintf(stderr, "Error deleting file %s\n", kTempFilename);
		exit(1);
	}
	
	
	/* Run the assembler */
	if (clopt->assemble)
	{
		int pid;
		if ((pid = fork()) == 0)	/* Child process */
		{
			execlp(VASM, "vasm", clopt->outputFile, NULL);
			/* UNREACHED */
		}
		else
		{
			waitpid(pid, &status, 0);
		}
	}

	/* Clean up the assembly file */
	if (clopt->clobberAsm && remove(clopt->outputFile))
	{
		fprintf(stderr, "Error deleting file %s\n", clopt->outputFile);
		exit(1);
	}
			
	/* If all is well, we've reached this point and the file has been compiled */
	return 0;
}


int cpp(char *cppOpts)
{
	char *cmd;
	int i;
	
	extern FILE *yyin;
	extern FILE *popen();
	
	
	if (!(cmd = (char *)calloc(strlen(cppOpts)+1+sizeof(CPP), sizeof(char))))
		return -1;	/* No room */
				
	strcpy(cmd, CPP);
	
	if (strlen(cppOpts) > 0)
	{
		strcat(cmd, " -");
		strcat(cmd, cppOpts);
	}
	
	
	if (yyin = popen(cmd, "r"))
		i = 0;
	else
		i = -1;
	
	free(cmd);
	return i;
}


Options *parse_cmdline(int argc, char **argv)
{
	Options *o = (Options *)malloc(sizeof(Options));
	char **argp = argv;
	char *opts = "CDEIUPalpo:st";
	int  arg;
	int i;
	
	extern int  optind;
	extern char *optarg;
	
	
	/* Set the defaults */
	o->runCpp = true;
	o->compile = true;
	o->link = true;
	o->assemble = true;
	o->clobberTmp = true;
	o->clobberAsm = true;
	
	o->cppOptions[0] = '\0';
	o->inputFile[0] = '\0';
	
	while ((arg = getopt(argc, argv, opts)) != -1)
	{
		switch (arg)
		{
		case 'C':
		case 'D':
		case 'E':
		case 'I':
		case 'U':
		case 'P':
			strncat(o->cppOptions, (char *)&arg, 1);
			break;
		
		case 'l':
			o->link = false;
		case 't':
			o->clobberTmp = false;
			break;

		case 's':
			o->assemble = false;
		case 'a':
			o->clobberAsm = false;
			break;
		case 'p':
			o->runCpp = false;
			break;
		case 'o':
			o->clobberAsm = false;
			if (optarg != NULL)
				strcpy(o->outputFile, optarg);
			else
				usage(PROG);
			break;
		default:
			fprintf(stderr, "%c is not a valid option.\n", arg);
			usage(PROG);
		}
	}
	argc -= optind;
	argv += optind;
	
	if (*argv == NULL)
	{
		fprintf(stderr, "No input file specified\n");
		usage(PROG);
	}
	
	strcpy(o->inputFile, *argv);
	if (*(argv+1) != NULL)
	{
		fprintf(stderr, "Invalid argument: %s\n", *(argv+1));
		usage(PROG);
	}
	
	/* For debugging purposes */
	ShowOptions(o);
	
	return o;
}


void	ShowOptions(const Options *o)
{
	
#ifdef TRACE
	
	printf("Source file: %s\n", o->inputFile);
	printf("Run preprocessor: %d\n", o->runCpp);
	if (o->runCpp)
		printf("CPP options: %s\n", o->cppOptions);
	printf("Link? %d\n", o->link);
	printf("Assemble? %d\n", o->assemble);
	printf("Save temp? %d\n", o->clobberTmp);
	printf("Save assembly? %d\n", o->clobberAsm);
	
#endif
}


