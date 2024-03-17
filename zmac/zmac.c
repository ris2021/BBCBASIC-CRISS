
/*  A Bison parser, made from zmac.y
 by  GNU Bison version 1.27
  */

#define YYBISON 1  /* Identify Bison output.  */

#define	STRING	257
#define	NOOPERAND	258
#define	ARITHC	259
#define	ADD	260
#define	LOGICAL	261
#define	AND	262
#define	OR	263
#define	XOR	264
#define	ANDAND	265
#define	OROR	266
#define	BIT	267
#define	CALL	268
#define	INCDEC	269
#define	DJNZ	270
#define	EX	271
#define	IM	272
#define	PHASE	273
#define	DEPHASE	274
#define	TK_IN	275
#define	JR	276
#define	LD	277
#define	TK_OUT	278
#define	PUSHPOP	279
#define	RET	280
#define	SHIFT	281
#define	RST	282
#define	REGNAME	283
#define	IXYLH	284
#define	ACC	285
#define	TK_C	286
#define	RP	287
#define	HL	288
#define	INDEX	289
#define	AF	290
#define	TK_F	291
#define	AFp	292
#define	SP	293
#define	MISCREG	294
#define	COND	295
#define	SPCOND	296
#define	NUMBER	297
#define	UNDECLARED	298
#define	END	299
#define	ORG	300
#define	ASSERT	301
#define	TSTATE	302
#define	T	303
#define	TILO	304
#define	TIHI	305
#define	SETOCF	306
#define	OCF	307
#define	LOW	308
#define	HIGH	309
#define	DC	310
#define	DEFB	311
#define	DEFD	312
#define	DEFS	313
#define	DEFW	314
#define	DEF3	315
#define	EQU	316
#define	DEFL	317
#define	LABEL	318
#define	EQUATED	319
#define	WASEQUATED	320
#define	DEFLED	321
#define	COMMON	322
#define	MULTDEF	323
#define	SHL	324
#define	SHR	325
#define	LT	326
#define	EQ	327
#define	LE	328
#define	GE	329
#define	NE	330
#define	NOT	331
#define	MROP_ADD	332
#define	MROP_SUB	333
#define	MROP_MUL	334
#define	MROP_DIV	335
#define	MROP_MOD	336
#define	MROP_AND	337
#define	MROP_OR	338
#define	MROP_XOR	339
#define	MROP_NE	340
#define	MROP_EQ	341
#define	MROP_LT	342
#define	MROP_GT	343
#define	MROP_LE	344
#define	MROP_GE	345
#define	MROP_SHIFT	346
#define	MROP_SHL	347
#define	MROP_SHR	348
#define	MROP_NOT	349
#define	MROP_LOW	350
#define	MROP_HIGH	351
#define	IF_TK	352
#define	IFE_TK	353
#define	IF1_TK	354
#define	IF2_TK	355
#define	IF_DEF_TK	356
#define	IF_CP_TK	357
#define	ELSE_TK	358
#define	ENDIF_TK	359
#define	ARGPSEUDO	360
#define	INCBIN	361
#define	LIST	362
#define	MINMAX	363
#define	MACRO	364
#define	MNAME	365
#define	ARG	366
#define	ENDM	367
#define	ONECHAR	368
#define	TWOCHAR	369
#define	JRPROMOTE	370
#define	JPERROR	371
#define	PUBLIC	372
#define	EXTRN	373
#define	MRAS_MOD	374
#define	SETSEG	375
#define	INSTSET	376
#define	LXI	377
#define	DAD	378
#define	STAX	379
#define	STA	380
#define	SHLD	381
#define	LDAX	382
#define	LHLD	383
#define	LDA	384
#define	MVI	385
#define	MOV	386
#define	INXDCX	387
#define	INRDCR	388
#define	PSW	389
#define	JUMP8	390
#define	JP	391
#define	CALL8	392
#define	ALUI8	393
#define	SPECIAL	394
#define	RAWTOKEN	395
#define	LOCAL	396
#define	LD_XY	397
#define	ST_XY	398
#define	MV_XY	399
#define	ALU_XY	400
#define	BIT_XY	401
#define	SHIFT_XY	402
#define	INP	403
#define	OUTP	404
#define	JR_COND	405
#define	LDST16	406
#define	ARITH16	407
#define	REPT	408
#define	IRPC	409
#define	IRP	410
#define	EXITM	411
#define	NUL	412
#define	MPARM	413
#define	TK_IN0	414
#define	TK_OUT0	415
#define	MLT	416
#define	TST	417
#define	TSTIO	418
#define	LALL	419
#define	SALL	420
#define	XALL	421
#define	GT	422
#define	UNARY	423

#line 1 "zmac.y"

// GWP - keep track of version via hand-maintained date stamp.
#define VERSION "18oct2022"

/*
 *  zmac -- macro cross-assembler for the Zilog Z80 microprocessor
 *
 *  Bruce Norskog	4/78
 *
 *  This assembler is modeled after the Intel 8080 macro cross-assembler
 *  for the Intel 8080 by Ken Borgendale.  The major features are:
 *	1.  Full macro capabilities
 *	2.  Conditional assembly
 *	3.  A very flexible set of listing options and pseudo-ops
 *	4.  Symbol table output
 *	5.  Error report
 *	6.  Elimination of sequential searching
 *	7.  Commenting of source
 *	8.  Facilities for system definition files
 *
 * Revision History:
 *
 * jrp	3-8-82	Converted to run on Vax, updated syntax to conform better
 *		to the Zilog standard.
 *
 * jrp	3-15-82	Added underscore as a character type in the lex table
 *		'numpart' (0x5F).
 *
 *		Changed maximum number of characters in a label to 15
 *		from 7. Note that 'putsymtab' uses this value inside
 *		of a quoted string, so we use 15.
 *
 * jrp	2-15-83	Fixed 'getlocal' to return better local labels. It used
 *		to crash after 6 invocations.
 *
 * jrp	6-7-83	Fixed bug in the ADD IX,... instruction.
 *
 * jrp	5-11-84	Added code to print unused labels out with the symbol table
 *		Also sped up the macro processor by using stdio.
 *
 * jrp 5-22-84	Added include files ala ormac
 *
 * jrp 8-27-84	Added PHASE/DEPHASE commands
 *
 * cdk 9-20-86	Converted to run on a Pyramid.  This meant changing yylval
 *		to be a %union, and then putting in the appropriate
 *		typecasts where ints are pointers are used interchangeably.
 *		The current version still probably won't run on machines where
 *		sizeof(int) != sizeof(char *).
 *		Also changed emit() to use varargs, and got rid of the
 *		old style = in front of yacc action code.
 *			-Colin Kelley  vu-vlsi!colin
 *
 * cdk 10-2-86	Added some more typecasts to keep lint a little happier.
 *		Removed several unused variables.  Changed most vars
 *		declared as char to int, since many of them were being
 *		compared with -1!  I still don't know what's going on with
 *		est[][] being malloc'd and free'd everywhere...it looks pretty
 *		fishy...
 *
 * cdk 1-18-87  Added MIO code to emulate 'mfile' using malloc()'d memory.
 *		This was needed to get the code to work when compiled under
 *		MSC 4.0 on a PC, and it's probably faster anyway.
 *
 * cdk 2-5-87	Added 'cmp' as a synonym for 'cp', 'jmp' as a synonym for
 *		'jp', and added tolerance of accumulator specification for arithmetic
 *		and logical instructions.  (For example, 'or a,12' is now accepted,
 *		same as 'or 12'.)
 *
 * gwp 12-29-08	Changes to allow compilation with modern C compiler and using bison
 *		as the .y to .c converter.  assert, tstate pseudo-ops.
 *		t(), tilo(), tihi() functions.  ==, <=, >=, !=, !, <, > operators.
 *		-c to turn cycle counts off in listing.  Usage, -h and version.
 *
 * gwp 9-26-10	Add ocf() and setocf to track and set op code fetch counts.
 *		Add sett as an alias for tstate
 *
 * gwp 12-30-11	Add undocumented instructions sl1, pfix, pfiy, in (c), out (c),0
 *		bit/set/res (ixy+d),reg and ld/inc/dec ixylh.
 *
 * gwp 2-8-12   Increase MAXIFS massively due to massive lowt macro
 *
 * gwp 2-11-12  Support 32 bit constants.  '%' alias for MOD.  Add defd, dword.
 *		lo(x) and hi(x) for easy low and high byte extraction.  Allow
 *		filenames longer than 15 characters.  All output to "zout" subdirectory
 *		of source file.
 *
 * gwp 2-15-12	Perform multiple passes while equates are changing.  Support
 *		.label for temporary label definitions and _label for file
 *		scoped labels.  Allow '.' within labels.  Assert listing bugfix.
 *
 * gwp 4-27-12	Implement $ prefixed hex constants and double-quoted strings.
 *
 * gwp 6-30-12	Minor changes to allow compilation with gcc.
 *
 * gwp 9-05-12	incbin added.
 *
 * gwp 11-24-12	Fix macro expansion bug when symbol larger than MAXSYMBOLSIZE
 *		due to file name prepending when symbol starts with '_'.
 *
 * gwp 12-04-12	Optional JR promotion and JP demotion errors.  Output a warning
 *		if no execute address given.  Output ".bds" file to enable easy
 *		simple source level debugging.
 *
 * gwp 4-14-13	Parens in expressions, else, .pseudo, full set of C operators
 *		with conventional precedence and various aliases and code
 *		changes to make source similar to zmac 1.3 on internet.
 *
 * gwp 5-5-13	.cmd,.cas,.lcas,.bin output.  dc (both MACRO-80 and EDAS types).
 *		lo, hi renamed to low, high and make unary operators.  Allow
 *		label::, placeholder public, extern declarations.  Bug fixes
 *		in defs, t, ocf, tihi, tilo in phase mode.  Initial support
 *		for -I include directories. 0x hex constants. --mras flag for
 *		limited MRAS compatibility (allows $ in labels, $? to start
 *		labels).
 *
 * gwp 4-6-13	--rel for .rel (Microsoft linker) output and extern, public,
 *		aseg, cseg, dseg in support (big emit + expression revamp).
 *		-I follows C preprocessor convention, output relative to
 *		current directory.  8080 mnemonics, .z80, .8080, -z, -8.
 *		Change .bin to .cim.  Warn on labels not in first column.
 *
 * gwp 8-11-13	Allow $ to start identifiers and do '$' dropping when macro
 *              parsed so we no longer need to drop '$' in identifiers. 
 *              Even $FCB allowed, with warning.  Add --zmac for backwards
 *		compatibility with zmac.  ` now used for joining in macros.
 *		Most reserved words can be used as labels or variables.
 *		Free-form title, name, comment, subttl parsing.  Allow #arg
 *		for macro arguments (in --mras mode).  Support <CR> delimited
 *		files.  Add .ams output.  Integrate documentation (--doc).
 *
 * gwp 3-12-14	Emit jr even if out of range.  z80.lib support.
 *		Warning and bug fixes from Mark Galanger.
 *		Macros can override built-ins and are no longer listed
 *		in symbol table.  A, B, C, D, E, H, L, M, PSW, SP are
 *		pre-defined values which can be used in data statements
 *		(db, dw, dd).  Reserved words can be equated but are only
 *		accessbile in data.  SET can be used in place of DEFL
 *		(MAC and MACRO-80 agree on this).  '=' can be used in place
 *		of EQU. 'maclib file' includes 'file.lib'.  Bug fix in "dw 0,$".
 *		Removed error flagging in expressions which could cause parse
 *		to fail from that point onwards.
 *		expression(ix) equivalent to (ix + expression).
 *		Macro expanded lines didn't go through the line analyzer.
 *		Empty macro arguments (e.g., mac 1,,2)
 *		Implemented rept, irp, irpc, exitm.  Add more detail on phase
 *		errors. '' is an empty string in db/ascii/etc, 0 otherwise.
 *		Almost any name can be used as a macro parameter name.
 *		Allow 'if' in first column.
 *		Fix .rel mode bug in dc, incbin.
 *		Emit .bds output for dc, incbin.
 *		Allow assembly to wrap past end of memory.
 *		"pragma bds" for raw output to .bds file.  Also output equates
 *		to .bds file.
 *		Macro bug fix from Sergey Erokhin.
 *
 * gwp 9-5-16	Allow ' on identifiers for manual prime register tracking.
 *		Improve MRAS support with *LIST, *INCLUDE and Pk=n parameters.
 *
 * gwp 20-9-16	Big MRAS compatibility fixes.  Can do MRAS operator precedence,
 *		proper .operator. tokenization and agressive macro parameter
 *		substituion.  Change Pk=n to -Pk=n.  Add ++, += and variants
 *		for more compact variable adjustment than defl.  First crack
 *		at .tap output for ZX Spectrum support.
 *
 * gwp 13-8-17	Add "import" for simple once-only inclusion of files.
 *		Track full path so relative includes work properly.
 *		Allow push af', pop af' for notational convenience.
 *		Add "bytes" as alias for "dc".  Fix --rel output bugs in
 *		low(), high(), div and mod.
 *
 * gwp 12-3-18	250 baud .cas output and .wav format.  Common blocks.
 *		--oo, --xo, --od to control output.  Delete output on fail.
 *
 * gwp 2-6-18	1000 baud .cas ouput and .mds (MAME/MESS debug script) output.
 *
 * gwp 28-7-18	Double free of output files bug fix from Pedro Gimeno.  Don't
 *		output SYSTEM files if no entry point thanks to Tim Halloran.
 *
 * gwp 6-10-18	Stop quoted inclued file crash on for OSX (and linux?). Thanks
 *		to Paulo Silva. Added "dm" as "ascii" alias for Blair Robins.
 *
 * gwp 5-12-18	Peter Wilson ran into quoted include crash.  Also suggested
 *		import be allowed in column 0 and noted that keywords like
 *		IF and LIST could not be labels even if given colons.
 *
 * gwp 6-12-18	hex output does proper EOF record if no entry address given.
 *		include and some other pseudo-opts can have a label.
 *
 * gwp 3-1-19	Improve jrpromote to handle some edges cases better where
 *		promotion isn't needed as long as shortest code is tried first.
 *
 * gwp 5-1-19	Add cycle count and output bytes to macro invocations.
 *		[ with listing bug fixes added slightly later ]
 *
 * gwp 19-1-19	DRI compatibility enhancements and other bug fixes from
 *		Douglas Miller. TWOCHAR constants ('XY') usable everywhere.
 *		dolopt moved into function to stop LEX stack crash.  Support
 *		labels on cseg/dseg.  Relax paren parsing for LXI instruction.
 *		Recognize TITLE in column 0.  Stop "Not relocatable error" on
 *		"ORG 0".  -i option stops all macro line listing.
 *		--dri mode:
 *		silences warnings about builtin redefinition (for Z80.LIB).
 *		Strips '$' from constants and symbols.
 *		Accepts '*' in column 0 as comment.
 *		All 8080 opcodes can be use in DB and expressions.
 *		Add recognition of DRI $-MACRO directives
 *
 * gwp 20-1-19	Z-80 mnemonics usable as values.  --nmnv turns that off.  def3
 *		Register aliases.  Multiple statements per line roughed in.
 *
 * gwp 20-4-20	Preserve case of symbols in symbol table.  Output hexadecimal
 *		in upper case and show decimal value of symbols.
 *
 * tjh 9-5-20	Add -Dsym to allow definition of symbols on the command line.
 *		ZMAC_ARGS environment variable added to command line.
 *
 * gwp 25-8-20	Fix crash in "out (c),0".  Make "in f,(c)" work.
 *
 * gwp 17-3-21	Stop line buffer overflow when too many "dc" or "incbin" lines
 *		appear contiguously.  --fcal option and Z-180 instructions.
 *
 * gwp 10-4-21	Put code and data indications in .bds output.
 *
 * gwp 9-2-22	Fix --z180 and improve usage message on unknown -- flags.
 *
 * gwp 10-4-22	Much better symbol table hash function from Al Petrofsky as
 *		used in gcc and gas.
 *
 * abog 18-4-22	Added two flags --dotlocals and --filelocals
 *		--dotlocals makes labels that start with '.' local between labels.
 *		--filelocals makes labels that start with '_' local for the file.
 *
 * gwp 18-10-22	Added *GET, IFEQ, IFEQ, IFLT, IFGT to improved MRAS support.
 *		Change FILE/EXT to FILE.EXT for includes in --mras mode.
 *		xh, xl, yh, yl, hx, lx, hy, ly alternates for ixh, ixy, iyh, iyl.
 *
 * gwp 21-1-24	%% expansion in macro to improve MRAS compatibility.
 */

#if defined(__GNUC__)
#pragma GCC diagnostic error "-Wreturn-type"
#endif

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdarg.h>
#include <time.h>
#include <sys/stat.h>

#ifdef WIN32
#include <windows.h>	// just for colouring the output
#include <direct.h>		// _mkdir
#ifdef _MSC_VER
#define strdup _strdup
#define unlink _unlink
#define strncasecmp _strnicmp
#endif
#endif

#if defined(__APPLE__) || defined(__linux__) || defined(__FreeBSD__)
#include <unistd.h>	// just for unlink
#endif

#include "zi80dis.h"

#ifdef vax11c
#define unlink(filename) delete(filename)
#endif

#include "mio.h"

/*
 * DEBUG turns on pass reporting.
 * DBUG enables -d to allow yacc/bison yydebug increment (but must be passed
 *	on the command line)
 * Macro debug and Token debug enables.
#define	DEBUG
#define	M_DEBUG	
#define	T_DEBUG
 */

#ifdef DBUG
#define YYDEBUG 1
#endif

#define ITEMTABLESIZE	100000
#define TEMPBUFSIZE	(1000+MAXSYMBOLSIZE)
#define LINEBUFFERSIZE	1000
#define EMITBUFFERSIZE	200
#define MAXSYMBOLSIZE	40
#define IFSTACKSIZE	20
// GWP - I use lots of if's with my lowt macro
#define MAXIFS		65536
#define TITLELEN	50
#define BINPERLINE	16
#define	PARMMAX		25
#define MAXEXP		25
#define SYMMAJIC	07203
#define	NEST_IN		32
#define MAXPASS		32
#define MAXINCPATH	32

int iflist();
int yylex();
int phaseaddr(int addr);
int nextchar();
int getcol();
int skipline(int ac);
int tokenofitem(int deftoken, int keyexclude, int keyinclude);
int getm();
int counterr();
int countwarn();
int convert(char *buf, char *bufend, int *overflow);

void yyerror(char *err)
{}		/* we will do our own error printing */

struct argparse {
	char *arg;	// output buffer for argument
	int argsize;	// size of output buffer
	int (*getch)(struct argparse *); // get next character
	int *peek;	// pointer single item pushback buffer
	int macarg;	// working on macro arguments

	char *user_ptr;	// state for getch
	int user_int;	// state for getch
	int user_peek;	// state for getch

	int didarg;	// internal parsing state
	int numarg;	// internal parsing state
};

int getarg(struct argparse *ap);

struct	item	{
	char	*i_string;
	int	i_value;
	int	i_token;
	int	i_uses;
	int	i_scope;
	int	i_chain;
	int	i_pass;
};

void itemcpy(struct item *dst, struct item *src);
int item_is_verb(struct item *i);
int item_value(struct item *i);
struct item *keyword(char *name);
int keyword_index(struct item *k);

#define SCOPE_NONE	(0)
#define SCOPE_PROGRAM	(1)
#define SCOPE_DATA	(2)
#define SCOPE_COMMON	(3)
#define SCOPE_PUBLIC	(4)
#define SCOPE_EXTERNAL	(8)
#define SCOPE_NORELOC	(16)
#define SCOPE_BUILTIN	(32)	/* abuse */
#define SCOPE_COMBLOCK	(64)
#define SCOPE_TWOCHAR	(128)
#define SCOPE_ALIAS	(256)
#define SCOPE_CMD_P	(512)
#define SCOPE_CMD_D	(1024)

#define SCOPE_SEGMASK	(3)
#define SCOPE_SEG(s)	((s) & SCOPE_SEGMASK)

struct expr {
	int e_value;
	int e_scope;
	int e_token;
	int e_parenthesized;
	struct item *e_item;
	struct expr *e_left;
	struct expr *e_right;
};

#define EXPR_SEG(e)	SCOPE_SEG(e->e_scope)

FILE	*fout,
	*fbuf,
	*fbds,
	*fcmd,
	*fcas,
	*flcas,
	*flnwcas,
	*ftcas,
	*fcim,
	*fams,
	*frel,
	*ftap,
	*fmds,
	*f1500wav,
	*f1000wav,
	*f500wav,
	*f250wav,
	*fin[NEST_IN],
	*now_file ;

char *output_dir = "zout";

struct OutputFile {
	char *suffix;
	char *mode;
	FILE **fpp;
	int system; // A cassette SYSTEM file
	int no_open;
	int wanted; // output file has been explicitly selected
	char *filename;
	int temp;
}
outf[] = {
	{ "lst",	"w",	&fout		},
	{ "hex", 	"w",	&fbuf		},
	{ "bds",	"w",	&fbds		},
	{ "cmd",	"wb",	&fcmd		},
	{ "1500.wav",	"wb",	&f1500wav, 1	}, // must be 1 before 1500.cas
	{ "1500.cas",	"w+b",	&fcas,	   1	},
	{ "1000.wav",	"wb",	&f1000wav, 1	}, // must be 1 before 1000.cas
	{ "1000.cas",	"w+b",	&flnwcas,  1	},
	{ "500.wav",	"wb",	&f500wav,  1	}, // must be 1 before 500.cas
	{ "500.cas",	"w+b",	&flcas,    1	},
	{ "250.wav",	"wb",	&f250wav	}, // must be 1 before 250.cas
	{ "250.cas",	"w+b",	&ftcas		},
	{ "cim",	"wb",	&fcim		},
	{ "ams",	"wb",	&fams		},
	{ "rel",	"wb",	&frel,	0, 1	},
	{ "tap",	"wb",	&ftap		},
	{ "mds",	"w",	&fmds		},
};
#define CNT_OUTF (sizeof outf / sizeof outf[0])

int getoptarg(int argc, char *argv[], int i);
void stop_all_outf();
void clean_outf();
void clean_outf_temp();
void suffix_list(char *sfx_lst, int no_open);

int	pass2;	/*set when pass one completed*/
int	outpass; 	// set when we decide to stop doing passes */
int	passfail;	// set when an error means passes should not continue
int	passretry;	// set when an inconsistency will require another pass
int	dollarsign ;	/* location counter */
int	olddollar ;	/* kept to put out binary */
int	oldothdollar;	// output address of next .cmd/.cas/.lcas block
int	emit_addr;	// where code and data are being placed in memory
int	tstates;	// cumulative T-states
int	ocf;		// cumulative op code fetches
int	llseq;		// local label sequence number
int	mras;		// MRAS semi-compatibility mode
int	trueval = 1;	// Value returned for boolean true
int	zcompat;	// Original zmac compatibility mode
int	dot_locals;	// If this is set, labels that start with a '.' will be local between labels
int	file_locals;	// If this is set, labels that start with a '_' will be local to the file
char	modstr[8];	// Replacement string for '?' in labels when MRAS compatible
int	relopt;		// Only output .rel files and length of external symbols
int	driopt;		// DRI assemblers compatibility
int	macopt;		// DRI assemblers $-MACRO et al.
int	comnt;		// DRI assemblers '*' comment line
int	nmnvopt;	// Mnemonics are not treated as predefined values.
char	progname[8];	// Program name for .rel output
int	note_depend;	// Print names of files included
int	separator;	// Character that separates multiple statements.
int	firstcol;
int	logcol;
int	coloncnt;
int first_always_label;
int	full_exprs;	// expression parsing mode allowing almost any identifier
struct item *label, pristine_label; // 
int	list_dollarsign;// flag used to change list output for some operations
int	list_addr;	// address to display for operation if !list_dollarsign

// Include file search path
char	*incpath[MAXINCPATH];
int	incpath_cnt;

/* program counter save for PHASE/DEPHASE */
int	phdollar, phbegin, phaseflag ;

char	*src_name[NEST_IN] ;
int	linein[NEST_IN] ;
int linepeek[NEST_IN];
int	now_in ;


// These first 5 errors are singled out in lsterr1() for reasons I don't
// quite understand.
#define bflag	0	/* balance error */
#define eflag	1	/* expression error */
#define fflag	2	/* syntax error */
#define iflag	3	/* bad digits */
#define mflag	4	/* multiply defined */

#define pflag	5	/* phase error */
#define uflag	6	/* undeclared used */
#define vflag	7	/* value out of range */
#define oflag	8	/* phase/dephase error */
#define aflag	9	/* assert failed */
#define jflag	10	/* JP could be JR */
#define rflag	11	/* expression not relocatable */
#define gflag	12	/* incorrect register */
#define zflag	13	/* invalid instruction */

#define FIRSTWARN	warn_hex
#define	warn_hex	14
#define warn_notimpl	15
#define warn_general	16

#define FLAGS	17	/* number of errors and warnings */

char	err[FLAGS];
int	keeperr[FLAGS];
char	errlet[FLAGS]="BEFIMPUVOAJRGZHNW";
char	*errname[FLAGS]={
	"Balance",
	"Expression",
	"Syntax",
	"Digit",
	"Mult. def.",
	"Phase",
	"Undeclared",
	"Value",
	"Phase/Dephase",
	"Assertion failure",
	"Use JR",
	"Not relocatable",
	"Register usage",
	"Invalid instruction",
	"$hex constant interpreted as symbol",
	"Not implemented",
	"General"
};
char	errdetail[FLAGS][TEMPBUFSIZE * 2];
char	detail[TEMPBUFSIZE * 2];


unsigned char inpbuf[LINEBUFFERSIZE];
unsigned char inpbuf_insert[LINEBUFFERSIZE];
unsigned char *inpptr;

char	linebuf[LINEBUFFERSIZE];
char	*lineptr;
char	*linemax = linebuf+LINEBUFFERSIZE;

char	outbin[BINPERLINE];
char	*outbinp = outbin;
char	*outbinm = outbin+BINPERLINE;

char	outoth[256];
int	outoth_cnt = 0;

unsigned char	emitbuf[EMITBUFFERSIZE];
unsigned char	*emitptr;

char	ifstack[IFSTACKSIZE];
char	*ifptr;
char	*ifstmax = ifstack+IFSTACKSIZE-1;


char	hexadec[] = "0123456789ABCDEF" ;


int	nitems;
int	nbytes;
int	invented;
int	npass;
int	njrpromo;
int	multiline;
int	prev_multiline;


char	tempbuf[TEMPBUFSIZE];
char	*tempmax = tempbuf+TEMPBUFSIZE-1;

char	arg_flag;
struct argparse arg_state;
void	arg_start();
void	arg_reset();
int	str_getch(struct argparse *ap);

int	mras_undecl_ok;
int	mras_param[10];
int	mras_param_set[10];

struct cl_symbol {
	char *name;
	struct cl_symbol *next;
} *cl_symbol_list;

char	inmlex;
char	mlex_list_on;
int	parm_number;
int	exp_number;
char	symlong[] = "Symbol/number too long";
int	raw;

int	disp;

int	param_parse;
#define PARAMTABSIZE (PARMMAX * 2)
struct item paramtab[PARAMTABSIZE];

#define FLOC	PARMMAX
#define TEMPNUM	PARMMAX+1
#define REPNUM	PARMMAX+2
#define MSTART	PARMMAX+3
#define MSTR	PARMMAX+4
#define MARGP	PARMMAX+5
#define MIF	PARMMAX+6
#define MNUMPAR	PARMMAX+7

#define PAREXT	8

union exprec {
	char *param;
	int value;
	struct argparse *ap;
};
union exprec	*est;
union exprec	*est2;
union exprec	*expstack[MAXEXP];
int	expptr;

int	floc;
int	mfptr;
FILE	*mfile;

char	*writesyms;


char	*title;
char	titlespace[TITLELEN];
char	*subtitle;
char	subtitlespace[TITLELEN];
char	*timp;
char	*sourcef;
/* changed to cope with filenames longer than 14 chars -rjm 1998-12-15 */
char	src[1024];
char	bin[1024];
char	listf[1024];
char	oth[1024];

char	copt = 1,	/* cycle counts in listings by default */
	edef = 1,
	eopt = 1,
	fdef = 0,
	fopt = 0,
	gdef = 1,
	gopt = 1,
	iopt = 0 ,	/* list include files */
	jopt = 0,
	JPopt = 0,
	lstoff = 0,
	lston = 0,	/* flag to force listing on */
	mdef = 0,
	mopt = 0,
	nopt = 1 ,	/* line numbers on as default */
	popt = 1,	/* form feed as default page eject */
	sopt = 0,	/* turn on symbol table listing */
	topt = 1,	/* terse, only error count to terminal */
	printer_output = 0, // GWP - printer style output
	z80 = 1;

char default_jopt, default_JPopt, default_z80 = 1;

char	xeq_flag = 0;
int	xeq;

time_t	now;
int	line;
int	page = 1;

struct stab {
	char	t_name[MAXSYMBOLSIZE+1];
	int	t_value;
	int	t_token;
};

// GWP - support for cycle count tracking (and opens door for efficient .cmd, etc. output)

unsigned char memory[1 << 16];
char memflag[1 << 16];
enum {
	MEM_DATA = 1,
	MEM_INST = 2,
	MEM_T_SET = 4
};
int tstatesum[1 << 16];
int ocfsum[1 << 16];

// GWP - expression handling extensions for .rel output.
void advance_segment(int step);
void expr_reloc_check(struct expr *ex);
void expr_number_check(struct expr *ex);
void expr_scope_same(struct expr *ex1, struct expr *ex2);
void expr_word_check(struct expr *ex);
int is_number(struct expr *ex);
int is_external(struct expr *ex);
struct expr *expr_num(int value);
struct expr *expr_alloc(void);
struct expr *expr_var(struct item *var);
struct expr *expr_mk(struct expr *left, int token, struct expr *right);
struct expr *expr_op(struct expr *left, int token, struct expr *right, int value);
struct expr *expr_op_sc(struct expr *left, int token, struct expr *right, int value);
void expr_free(struct expr *ex);
int can_extend_link(struct expr *ex);
void extend_link(struct expr *ex);
void putrelop(int op);
#define RELOP_BYTE	(1)
#define RELOP_WORD	(2)
#define RELOP_HIGH	(3)
#define RELOP_LOW	(4)
#define RELOP_NOT	(5)
#define RELOP_NEG	(6)
#define RELOP_SUB	(7)
#define RELOP_ADD	(8)
#define RELOP_MUL	(9)
#define RELOP_DIV	(10)
#define RELOP_MOD	(11)
struct item *item_lookup(char *name, struct item *table, int table_size);
struct item *item_substr_lookup(char *name, int token, struct item *table, int table_size);
struct item *locate(char *name);
// Data descriptions for emit()
#define E_CODE		(0)
#define E_DATA		(1)
#define E_CODE8		(2)
#define E_CODE16	(3)
int segment;
#define SEGCHAR(s) " '\"!"[s]
#define SEG_ABS		(0)
#define SEG_CODE	(1)
#define SEG_DATA	(2)
#define SEG_COMMON	(3)
int seg_pos[4]; // may eventually support SEG_COMMON
int seg_size[4];
int rel_main;
int segchange;
struct item *cur_common;
void putout(int value);
int outrec;
int outlen;
unsigned char outbuf[1024 * 1024];
void bookmark();
void listfrombookmark();


/*
 *  push back character
 */
#define NOPEEK (EOF - 1)
int	peekc;
int	nextline_peek;

/* function prototypes */
void error(char *as);
void usage(char *msg, char *param);
void help();
void list_out(int optarg, char *line_str, char type);
void erreport();
void errorprt(int errnum);
void errwarn(int errnum, char *message);
void mlex(char *look);
void popsi();
void suffix(char *str, char *suff);
char *basename(char *filename);
char *getsuffix(char *str);
void outpath(char *out, char *src, char *suff);
void casname(char *out, char *src, int maxlen);
void putm(int c);
void insymtab(char *name);
void outsymtab(char *name);
void compactsymtab();
void putsymtab();
void clear();
void clear_instdata_flags();
void setmem(int addr, int value, int type);
void setvars();
void flushbin();
void flushoth();
void lineout();
void puthex(int byte, FILE *buf);
void putcas(int byte);
void padcas();
void putrelbits(int count, int bits);
void putrel(int byte);
void putrelname(char *str);
void putrelextaddr(int extaddr);
void putrelcmd(int cmd);
void putrelsegref(int scope, int addr);
void flushrel(void);
void lsterr1();
void lsterr2(int lst);
void copyname(char *st1, char *st2);
void next_source(char *sp, int always);
void incbin(char *filename);
void dc(int count, int value);
char *getmraslocal();
void write_tap(int len, int org, unsigned char *data);
void write_250(int low, int high);
void writewavs(int pad250, int pad500, int pad1500);
void reset_import();
int imported(char *filename);
int sized_byteswap(int value);

#define RELCMD_PUBLIC	(0)
#define RELCMD_COMMON	(1)
#define RELCMD_PROGNAME	(2)
#define RELCMD_LIBLOOK	(3)
#define RELCMD_EXTLINK	(4)
#define RELCMD_COMSIZE	(5)
#define RELCMD_EXTCHAIN	(6)
#define RELCMD_PUBVALUE	(7)
#define RELCMD_EXTMINUS	(8)
#define RELCMD_EXTPLUS	(9)
#define RELCMD_DATASIZE	(10)
#define RELCMD_SETLOC	(11)
#define RELCMD_CODESIZE	(13)
#define RELCMD_ENDMOD	(14)
#define RELCMD_ENDPROG	(15)

/*
 *  add a character to the output line buffer
 */
void addtoline(int ac)
{
	/* check for EOF from stdio */
	if (ac == -1)
		ac = 0 ;
	if (lineptr >= linemax)
		error("line buffer overflow");
	*lineptr++ = ac;
}

int get_tstates(unsigned char *inst, int *low, int *high, int *fetch, char *dis)
{
	return zi_tstates(inst, z80, low, high, fetch, dis);
}

/*
 *  put values in buffer for outputing
 */

void emit(int bytes, int desc, struct expr *data, ...)
{
	int type, i, args, dsize;
	va_list ap;

	if (relopt && segchange) {
		segchange = 0;
		putrelcmd(RELCMD_SETLOC);
		putrelsegref(segment, seg_pos[segment]);
	}

	// External references only supported in .rel output.
	if (!relopt && data && (data->e_scope & SCOPE_EXTERNAL)) {
		sprintf(detail, "External references only allowed in .rel output\n");
		errwarn(uflag, detail);
	}

	va_start(ap, data);

	type = desc == E_DATA ? MEM_DATA : MEM_INST;

	// Check emit is not adding instructions to the buffer.
	if (desc != E_DATA && emitptr != emitbuf)
		fprintf(stderr, "internal inconsistency in t-state counting\n");

	dsize = 0;
	args = bytes;
	if (desc == E_DATA) {
		args = 0;
		dsize = bytes;
	}
	else if (desc == E_CODE16)
		dsize = 2;
	else if (desc == E_CODE8)
		dsize = 1;

	for (i = 0; i < args; i++)
	{
		if (emitptr >= &emitbuf[EMITBUFFERSIZE])
			error("emit buffer overflow");
		else {
			int addr = (emit_addr + (emitptr - emitbuf)) & 0xffff;
			*emitptr = va_arg(ap, int);
			if (segment == SEG_CODE) 
				setmem(addr, *emitptr, type);
			putrel(*emitptr);
			putout(*emitptr);
			emitptr++;
		}
	}

	va_end(ap);

	for (i = 0; i < dsize; i++) {
		int addr = (emit_addr + (emitptr - emitbuf)) & 0xffff;
		*emitptr = data->e_value >> (i * 8);
		if (segment == SEG_CODE)
			setmem(addr, *emitptr, type);
		putout(*emitptr);
		emitptr++;
	}

	if (desc != E_DATA)
	{
		int eaddr = emit_addr, low, fetch, addr_after;

		get_tstates(emitbuf, &low, 0, &fetch, 0);

		// emitbuf is OK since this only happens with single emits
		int op = emitbuf[0] & 0xff;

		switch (z80) {
		case 0:
			// 8080 mode, error if Z-80 instructions.
			if (op == 0x08 || op == 0x10 || op == 0x18 ||
			    op == 0x20 || op == 0x28 || op == 0x30 ||
			    op == 0x38 || op == 0xCB || op == 0xD9 ||
			    op == 0xDD || op == 0xED || op == 0xFD)
			{
				errwarn(zflag, "Invalid 8080 instruction");
			}
			break;
		case 1: // Z-80 mode, error if Z-180 instructions
			if (op == 0xED && (
			    (emitbuf[1] & 0xC6) == 0 || // IN0, OUT0
			    (emitbuf[1] & 0xC7) == 4 || // TST r
			    (emitbuf[1] & 0xCF) == 0x4C || // MLT rr
			    emitbuf[1] == 0x64 || // TST m
			    emitbuf[1] == 0x74 || // TSTIO (m)
			    emitbuf[1] == 0x83 || // OTIM
			    emitbuf[1] == 0x93 || // OTIMR
			    emitbuf[1] == 0x8B || // OTDM
			    emitbuf[1] == 0x9B || // OTDMR
			    emitbuf[1] == 0x76)) // SLP
			{
				errwarn(zflag, "Invalid Z-80 instruction");
			}
			break;
		case 2:
			// Z-180 mode, error if undocumented Z-80 instructions
			// So many undocumented Z-80 instructions that I lean
			// on get_states() to answer.
			if (low <= 0)
				errwarn(zflag, "Invalid Z-180 instruction");
			break;
		}

		// Special case to catch promotion of djnz to DEC B JP NZ
		// Even update the tstatesum[] counter though that seems to
		// me to be above and beyond.
		if (emitbuf[0] == 5 && args == 2) {
			tstatesum[eaddr] = tstates;
			ocfsum[eaddr] = ocf;
			memflag[eaddr] |= MEM_T_SET;
			eaddr++;
			tstates += low;
			ocf += fetch;
			low = 10;
			// still 1 fetch
		}

		// Sanity check
		if (low <= 0 && !err[zflag])
		{
			fprintf(stderr, "undefined instruction on %02x %02x (assembler or disassembler broken)\n",
				emitbuf[0], emitbuf[1]);
		}


		// Double setting of both sides of tstatesum[] seems like too
		// much, but must be done in the isolated instruction case:
		// org x ; inc a ; org y

		tstatesum[eaddr] = tstates;
		ocfsum[eaddr] = ocf;
		memflag[eaddr] |= MEM_T_SET;

		// Well, OK, should we default to high or low???
		// Guess it should be whatever makes sense for you
		// to get here which, generally, is the low.

		// low it is.

		tstates += low;
		ocf += fetch;

		addr_after = (emit_addr + (emitptr - emitbuf)) & 0xffff;

		tstatesum[addr_after] = tstates;
		ocfsum[addr_after] = ocf;
		memflag[addr_after] |= MEM_T_SET;
	}

	if (relopt && outpass && dsize > 0) {
		if (dsize == 1) {
			if (is_number(data))
				putrel(data->e_value);
			else if (can_extend_link(data)) {
				extend_link(data);
				putrelop(RELOP_BYTE);
				putrel(0);
			}
			else {
				err[rflag]++;

				putrel(0);
			}
		}
		else if (dsize == 2) {
			int handled = 0;
			if (data->e_scope & SCOPE_EXTERNAL) {
				struct item *var = 0;
				int offset = 0;
				// Simple external reference.
				if (is_external(data))
					var = data->e_item;
				else if (is_external(data->e_left) &&
					data->e_token == '+' &&
					is_number(data->e_right))
				{
					var = data->e_left->e_item;
					offset = data->e_right->e_value;
				}
				else if (is_number(data->e_left) &&
					data->e_token == '+' &&
					is_external(data->e_right))
				{
					offset = data->e_left->e_value;
					var = data->e_right->e_item;
				}
				else if (is_external(data->e_left) &&
					data->e_token == '-' &&
					is_number(data->e_right))
				{
					var = data->e_left->e_item;
					offset = data->e_right->e_value;
				}

				if (var && offset) {
					putrelcmd(data->e_token == '-' ?
						RELCMD_EXTMINUS : RELCMD_EXTPLUS);
					// Theoretically we could put a
					// program or data relative value here...
					putrelsegref(SEG_ABS, offset);
				}

				if (var) {
					int addr;

					if (var->i_chain == 0) {
						putrel(0);
						putrel(0);
					}
					else if (var->i_chain >> 16) {
						putrelbits(1, 1);
						putrelextaddr(var->i_chain);
					}
					else {
						putrel(var->i_chain);
						putrel(var->i_chain >> 8);
					}

					addr = dollarsign + args;

					if (segment == SEG_ABS && phaseflag)
						addr = phdollar + (addr - phbegin);

					var->i_chain = (segment << 16) | (addr & 0xffff);
					handled = 1;
				}
			}
			else if (is_number(data)) {
				// nice constant value
				putrel(data->e_value);
				putrel(data->e_value >> 8);
				handled = 1;
			}
			else if (!(data->e_scope & SCOPE_NORELOC)) {
				// relocatable value
				putrelbits(1, 1);
				putrelbits(2, data->e_scope);
				putrelbits(8, data->e_value);
				putrelbits(8, data->e_value >> 8);
				handled = 1;
			}

			if (!handled) {
				if (can_extend_link(data)) {
					extend_link(data);
					putrelop(RELOP_WORD);
					putrel(0);
					putrel(0);
				}
				else {
					err[rflag]++;
					putrel(data->e_value);
					putrel(data->e_value >> 8);
				}
			}
		}
		else if (dsize == 4) {
			// Only numbers are allowed.
			if (data->e_scope != 0) {
				err[vflag]++;
				if (data->e_scope & SCOPE_NORELOC)
					err[rflag]++;
			}
			for (i = 0; i < dsize; i++)
				putrel(data->e_value >> (i * 8));
		}
		else
			error("internal dsize error");
	}
}

#define ET_NOARG_DISP	(0)
#define ET_NOARG	(1)
#define ET_BYTE		(2)
#define ET_WORD		(5)

void emit1(int opcode, int regvalh, struct expr *data, int type)
{
	if (type == ET_BYTE && (data->e_value < -128 || data->e_value > 255))
		err[vflag]++;

	if (regvalh & 0x10000) {
		switch (type) {
		case ET_NOARG_DISP:
			emit(2, E_CODE, 0, regvalh >> 8, opcode);
			break;
		case ET_BYTE:
			emit(2, E_CODE8, data, regvalh >> 8, opcode);
			break;
		}
	}
	else if (regvalh & 0x8000) {
		switch (type) {
		case ET_NOARG_DISP:
			if (opcode & 0x8000)
				emit(4, E_CODE, 0, regvalh >> 8, opcode >> 8, disp, opcode);
			else
				emit(3, E_CODE, 0, regvalh >> 8, opcode, disp);
			break;
		case ET_NOARG:
			emit(2, E_CODE, 0, regvalh >> 8, opcode);
			break;
		case ET_BYTE:
			emit(3, E_CODE8, data, regvalh >> 8, opcode, disp);
			break;
		case ET_WORD:
			emit(2, E_CODE16, data, regvalh >> 8, opcode);
		}
	} else
		switch(type) {
		case ET_NOARG_DISP:
		case ET_NOARG:
			if (opcode & 0100000)
				emit(2, E_CODE, 0, opcode >> 8, opcode);
			else
				emit(1, E_CODE, 0, opcode);
			break;
		case ET_BYTE:
			emit(1, E_CODE8, data, opcode);
			break;
		case ET_WORD:
			if (opcode & 0100000)
				emit(2, E_CODE16, data, opcode >> 8, opcode);
			else
				emit(1, E_CODE16, data, opcode);
		}
}




void emitdad(int rp1,int rp2)
{
	if (rp1 & 0x8000)
		emit(2, E_CODE, 0, rp1 >> 8, rp2 + 9);
	else
		emit(1, E_CODE, 0, rp2 + 9);
}


void emitjr(int opcode, struct expr *dest)
{
	int disp = dest->e_value - dollarsign - 2;

	if (dest->e_scope & SCOPE_NORELOC)
		err[rflag]++;

	// Can't relative jump to other segments or an external
	// However, without .rel output we default to the code segment
	// for various reasons thus we let "jr 0" (and such) be acceptable
	// in those cases.
	if (((relopt && (dest->e_scope & SCOPE_SEGMASK) != segment) ||
		(dest->e_scope & SCOPE_EXTERNAL) ||
		disp > 127 || disp < -128) && z80)
	{
		if (npass > 1 && jopt) {
			njrpromo++;
			switch (opcode) {
			case 0x10: // DJNZ
				emit(2, E_CODE16, dest, 0x05, 0xC2); // DEC B, JP NZ
				break;
			case 0x18: // JR
				emit(1, E_CODE16, dest, 0xC3); // JP
				break;
			case 0x20: // JR NZ
				emit(1, E_CODE16, dest, 0xC2); // JP NZ
				break;
			case 0x28: // JR Z
				emit(1, E_CODE16, dest, 0xCA); // JP Z
				break;
			case 0x30: // JR NC
				emit(1, E_CODE16, dest, 0xD2); // JP NC
				break;
			case 0x38: // JR C
				emit(1, E_CODE16, dest, 0xDA); // JP C
				break;
			default:
				err[vflag]++;	// shouldn't happen!
				expr_free(dest);
				break;
			}
		}
		else {
			emit(2, E_CODE, 0, opcode, -2);  // branch to itself
			err[vflag]++;
			expr_free(dest);
		}
	}
	else {
		emit(2, E_CODE, 0, opcode, disp);
		expr_free(dest);
	}
}

void checkjp(int op, struct expr *dest)
{
	op &= 0x030;
	// Only applies to Z-80 output and if JP optimization checking is on.
	// JR only has z, nz, nc, c
	// A jump to the current segment might have been optimizable
	if (z80 && JPopt && (op == 0 || op == 010 || op == 020 || op == 030) &&
		(dest->e_scope & (SCOPE_SEGMASK | SCOPE_EXTERNAL)) == segment)
	{
		int disp = dest->e_value - dollarsign - 2;
		if (disp >= -128 && disp <= 127)
			err[jflag]++;
	}
}

/*
 *  put out a byte of binary 
 */
void putbin(int v)
{
	if(!outpass) return;
	*outbinp++ = v;
	if (outbinp >= outbinm) flushbin();

	outoth[outoth_cnt++] = v;
	if (outoth_cnt == 256) flushoth();
}



/*
 *  output one line of binary in INTEL standard form
 */
void flushbin()
{
	char *p;
	int check=outbinp-outbin;

	if (!outpass)
		return;
	nbytes += check;
	if (check) {
		if (fbuf) {
			putc(':', fbuf);
			puthex(check, fbuf);
			puthex(olddollar>>8, fbuf);
			puthex(olddollar, fbuf);
			puthex(0, fbuf);
			check += (olddollar >> 8) + olddollar;
			olddollar += (outbinp-outbin);
			for (p=outbin; p<outbinp; p++) {
				puthex(*p, fbuf);
				check += *p;
			}
			puthex(256-check, fbuf);
			putc('\n', fbuf);
		}
		outbinp = outbin;
	}
}



/*
 *  put out one byte of hex
 */
void puthex(int byte, FILE *buf)
{
	putc(hexadec[(byte >> 4) & 017], buf);
	putc(hexadec[byte & 017], buf);
}

// Case-independent string comparisons.

int ci_strcompare(char *s1, char *s2, int len)
{
	int c1, c2;
	do {
		if (len == 0)
			return 0;

		c1 = *s1++;
		if (c1 >= 'A' && c1 <= 'Z') c1 += 'a' - 'A';
		c2 = *s2++;
		if (c2 >= 'A' && c2 <= 'Z') c2 += 'a' - 'A';
		if (c1 != c2)
			return c1 - c2;

		if (len > 0)
			if (--len == 0)
				return 0;

	} while (c1 && c2);

	return 0;
}

int ci_strcmp(char *s1, char *s2)
{
	return ci_strcompare(s1, s2, -1);
}

void flushoth()
{
	int i, checksum;

	if (!outpass || outoth_cnt == 0)
		return;

	if (fcmd) {
		fprintf(fcmd, "%c%c%c%c", 1, outoth_cnt + 2, oldothdollar, oldothdollar >> 8);
		fwrite(outoth, outoth_cnt, 1, fcmd);
	}

	putcas(0x3c);
	putcas(outoth_cnt);
	putcas(oldothdollar);
	putcas(oldothdollar >> 8);
	checksum = oldothdollar + (oldothdollar >> 8);
	for (i = 0; i < outoth_cnt; i++) {
		putcas(outoth[i]);
		checksum += outoth[i];
		if (fmds)
			fprintf(fmds, "b@$%04x=$%02x\n", oldothdollar + i, outoth[i] & 0xff);
	}
	putcas(checksum);

	oldothdollar += outoth_cnt;
	outoth_cnt = 0;
}

int casbit, casbitcnt = 0, cas_low_pad, cas_high_pad;

void putcas(int byte)
{
	if (flcas)
		fputc(byte, flcas);

	if (flnwcas)
		fputc(byte, flnwcas);

	if (fcas) {
		// Buffer 0 stop bit and the 8 data bits.
		casbit = (casbit << 9) | (byte & 0xff);
		casbitcnt += 9;
		while (casbitcnt >= 8) {
			casbitcnt -= 8;
			fputc(casbit >> casbitcnt, fcas);
		}
	}
}

void padcas()
{
	int pad = 6;
	int padbit = 8 - casbitcnt;

	cas_low_pad = cas_high_pad = pad * 8;

	if (fcas && padbit < 8) {
		fputc(casbit << padbit, fcas);
		cas_high_pad += padbit;
	}

	// "Play Cas" seems to require trailing zeros to work properly.
	while (pad-- > 0) {
		if (flcas)
			fputc(0, flcas);

		if (flnwcas)
			fputc(0, flnwcas);

		if (fcas)
			fputc(0, fcas);
	}
}

void casname(char *out, char *src, int maxlen)
{
	char *base = basename(src);
	int i;

	out[0] = 'N';
	for (i = 1; i < maxlen; i++)
		out[i] = ' ';

	for (i = 0; *base && i < maxlen; base++) {
		if (ci_strcmp(base, ".z") == 0 || ci_strcmp(base, ".asm") == 0)
			break;

		if (*base >= 'a' && *base <= 'z') {
			*out++ = *base - ('a' - 'A');
			i++;
		}
		else if (*base >= 'A' && *base <= 'Z') {
			*out++ = *base;
			i++;
		}
	}
}

int relbit, relbitcnt = 0;

void putrelbits(int count, int bits)
{
	if (!outpass || !relopt)
		return;

	relbit <<= count;
	relbit |= bits & ((1 << count) - 1);
	relbitcnt += count;

	while (relbitcnt >= 8) {
		relbitcnt -= 8;
		fputc(relbit >> relbitcnt, frel);
	}
}

void putrel(int byte)
{
	// Add 0 bit indicating byte to load at next counter
	putrelbits(1, 0);
	// Add byte to load
	putrelbits(8, byte);
}

void putrelname(char *str)
{
	int len = strlen(str);
	int maxlen = mras ? 7 : relopt;

	// .rel file format can do strings 7 long but for compatibility
	// we restrict them to 6.  I believe this is important because
	// extended link functions require a character when they wish to
	// operate on an external symbol.
	if (len > maxlen)
		len = maxlen;
	putrelbits(3, len);
	while (len-- > 0) {
		int ch = *str++;
		if (ch >= 'a' && ch <= 'z')
			ch -= 'a' - 'A';
		putrelbits(8, ch);
	}
}

void putrelsegref(int scope, int addr)
{
	putrelbits(2, scope);
	putrelbits(8, addr);
	putrelbits(8, addr >> 8);
}

void putrelextaddr(int extaddr)
{
	putrelsegref(extaddr >> 16, extaddr);
}


void putrelcmd(int relcmd)
{
	putrelbits(1, 1);
	putrelbits(2, 0);
	putrelbits(4, relcmd);
}

void flushrel(void)
{
	if (relbitcnt > 0)
		putrelbits(8 - relbitcnt, 0);

	if (relopt)
		fflush(frel);
}

void list_cap_line()
{
	if (multiline) {
		if (lineptr > linebuf)
			lineptr[-1] = separator;
		addtoline('\n');
	}
	addtoline('\0');

	prev_multiline = multiline;
	multiline = 0;
}

/*
 *  put out a line of output -- also put out binary
 */
void list(int optarg)
{
	list_cap_line();

	list_out(optarg, linebuf, ' ');

	lineptr = linebuf;
}

void delayed_list(int optarg)
{
	int delay = iflist() && !mopt;
	FILE *tmp = fout;

	fout = delay ? NULL : tmp;
	list(optarg);
	fout = tmp;
	bookmark(delay);
}

void list_optarg(int optarg, int seg, int type)
{
	if (seg < 0 || !relopt)
		seg = (relopt && !phaseflag) ? segment : SEG_ABS;

	puthex(optarg >> 8, fout);
	puthex(optarg, fout);
	fputc(SEGCHAR(seg), fout);
	if (type)
		fputc(type, fout);
}

void bds_perm(int dollar, int addr, int len)
{
	while (len > 0) {
		int blklen;
		int usage = memflag[addr & 0xffff] & (MEM_INST | MEM_DATA);

		for (blklen = 0; blklen < len; blklen++) {
			int u = memflag[(addr + blklen) & 0xffff] & (MEM_INST | MEM_DATA);
			if (u != usage)
				break;
		}

		int bu = 0;
		if (usage & MEM_INST) bu |= 1;
		if (usage & MEM_DATA) bu |= 2;

		while (blklen > 0) {
			int size = blklen;
			if (size > 255) size = 255;
			fprintf(fbds, "%04x %04x u %02x %02x\n",
				dollar, addr & 0xffff, size, bu);

			addr += size;
			dollar += size;
			len -= size;

			blklen -= size;
		}
	}
}

void list_out(int optarg, char *line_str, char type)
{
	unsigned char *	p;
	int	i;
	int  lst;

	if (outpass) {
		lst = iflist();
		if (lst) {
			lineout();
			if (nopt)
				fprintf(fout, "%4d:", linein[now_in]);

			if (copt)
			{
			    if (emitptr > emitbuf && (memflag[emit_addr] & MEM_INST))
			    {
			        int low, high, fetch;
			        get_tstates(memory + emit_addr, &low, &high, &fetch, 0);

				// Special case to catch promotion of djnz to DEC B JP NZ
				if (memory[emit_addr] == 5 && emitptr - emitbuf == 4) {
					low += 10;
					high += 10;
				}

			    	fprintf(fout, nopt ? "%5d" : "%4d", tstatesum[emit_addr]);

				fprintf(fout, "+%d", low);
				if (low != high)
				    fprintf(fout, "+%d", high - low);
			    }
			    else
			    {
			        fprintf(fout, nopt ? "%5s-" : "%4s-", "");
			    }
			}

			if (nopt || copt)
				fprintf(fout, "\t");

			list_optarg(optarg, -1, type);

			for (p = emitbuf; (p < emitptr) && (p - emitbuf < 4); p++) {
				puthex(*p, fout);
			}
			for (i = 4 - (p-emitbuf); i > 0; i--)
				fputs("  ", fout);

			putc('\t', fout);
			fputs(line_str, fout);
		}

		if (fbds) {
			if (emitptr > emitbuf) {
				fprintf(fbds, "%04x %04x d ", dollarsign, emit_addr);
				for (p = emitbuf; p < emitptr; p++)
					fprintf(fbds, "%02x", *p & 0xff);
				fprintf(fbds, "\n");

				bds_perm(dollarsign, emit_addr, emitptr - emitbuf);
			}
			fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, line_str);
		}

		for (p = emitbuf; p < emitptr; p++)
			putbin(*p);

		p = emitbuf+4;
		while (lst && gopt && p < emitptr) {
			lineout();
			if (nopt) putc('\t', fout);
			fputs("      ", fout);
			if (copt) fputs("        ", fout);
			for (i = 0; (i < 4) && (p < emitptr);i++) {
				puthex(*p, fout);
				p++;
			}
			putc('\n', fout);
		}

		lsterr2(lst);
	} else
		lsterr1();

	dollarsign += emitptr - emitbuf;
	emit_addr += emitptr - emitbuf;
	dollarsign &= 0xffff;
	emit_addr &= 0xffff;
	emitptr = emitbuf;
}



/*
 *  keep track of line numbers and put out headers as necessary
 */
void lineout()
{
	if (!printer_output || !fout)
		return;

	if (line == 60) {
		if (popt)
			putc('\014', fout);	/* send the form feed */
		else
			fputs("\n\n\n\n\n", fout);
		line = 0;
	}
	if (line == 0) {
		fprintf(fout, "\n\n%s %s\t%s\t Page %d\n%s\n\n",
			&timp[4], &timp[20], title, page++,
			subtitle ? subtitle : "");
		line = 4;
	}
	line++;
}


/*
 *  cause a page eject
 */
void eject()
{
	if (!printer_output)
		return;

	if (outpass && iflist()) {
		if (popt) {
			putc('\014', fout);	/* send the form feed */
		} else {
			while (line < 65) {
				line++;
				putc('\n', fout);
			}
		}
	}
	line = 0;
}


/*
 *  space n lines on the list file
 */
void space(int n)
{
	int	i ;
	if (outpass && iflist() && fout)
		for (i = 0; i<n; i++) {
			lineout();
			putc('\n', fout);
		}
}

/*
 *  Error handling - pass 1
 */
void lsterr1()
{
	int i;
	for (i = 0; i <= mflag; i++)
		if (err[i]) {
			if (topt)
				errorprt(i);
			passfail = 1;
			err[i] = 0;
		}
}


/*
 *  Error handling - pass 2.
 */
void lsterr2(int lst)
{
	int i;
	for (i=0; i<FLAGS; i++)
		if (err[i]) {
			if (i < FIRSTWARN)
				passfail = 1;
			if (lst) {
				char *desc = errname[i];
				char *type = i < FIRSTWARN ? " error" : " warning";
				if (errdetail[i][0]) {
					desc = errdetail[i];
					type = "";
				}
				lineout();
				if (fout)
					fprintf(fout, "%c %s%s\n",
						errlet[i], desc, type);
			}
			err[i] = 0;
			keeperr[i]++;
			if (i > mflag && topt)
				errorprt(i);
		}

	if (fout)
		fflush(fout);	/*to avoid putc(har) mix bug*/
}

/*
 *  print diagnostic to error terminal
 */
void errorprt(int errnum)
{
	char *desc = errname[errnum];
	char *type = errnum < FIRSTWARN ? " error" : " warning";
	if (errdetail[errnum][0]) {
		desc = errdetail[errnum];
		type = "";
	}
	fprintf(stderr, "%s(%d) : %s%s",
		src_name[now_in], linein[now_in], desc, type);

	errdetail[errnum][0] = '\0';

	fprintf(stderr, "\n");
	fprintf(stderr, "%s\n", linebuf);
	fflush(stderr) ;
}

void errwarn(int errnum, char *message)
{
	if (errnum == uflag && mras_undecl_ok)
		return;

	err[errnum]++;
	strcpy(errdetail[errnum], message);
}

/*
 *  list without address -- for comments and if skipped lines
 */
void list1()
{
	int lst;

	list_cap_line();
	lineptr = linebuf;
	if (outpass) {
		if ((lst = iflist())) {
			lineout();
			if (nopt)
				fprintf(fout, "%4d:\t", linein[now_in]);
			if (copt)
				fprintf(fout, "\t");
			fprintf(fout, "\t\t%s", linebuf);
			lsterr2(lst);
		}
		if (fbds)
			fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, linebuf);
	}
	else
		lsterr1();
}

void delayed_list1()
{
	int delay = iflist() && !mopt;
	FILE *tmp = fout;

	fout = delay ? NULL : tmp;
	list1();
	fout = tmp;

	bookmark(delay);
}

/*
 *  see if listing is desired
 */
int iflist()
{
	int problem;

	if (!fout)
		return 0;

	if (inmlex)
		return mlex_list_on;

	if (lston)
		return(1) ;
	if (*ifptr && !fopt)
		return(0);
	if (!lstoff && !expptr)
		return(1);
	problem = countwarn() + counterr();
	if (expptr) {
		if (problem) return(1);
		if (!mopt) return(0);
		if (mopt == 1) return(1);
		return(emitptr > emitbuf);
	}
	if (eopt && problem)
		return(1);
	return(0);
}

void do_equ(struct item *sym, struct expr *val, int call_list);
void do_defl(struct item *sym, struct expr *val, int call_list);

// GWP - This avoids an apparent bug in bison as it tries to start out the
// Not needed under gcc which defines __STDC__ so I guard it to prevent
// warnings.
// yyparse() function with yyparse() ; { }.
#ifndef __STDC__
#define __STDC__
#endif

#define PSTITL	(0)	/* title */
#define PSRSYM	(1)	/* rsym */
#define PSWSYM	(2)	/* wsym */
#define PSINC	(3)	/* include file */
#define PSMACLIB (4)	/* maclib (similar to include) */
#define PSIMPORT (5)	/* import file */
#define PSCMN	(6)	/* common block */

#define SPTITL	(0)	/* title */
#define SPSBTL	(1)	/* sub title */
#define SPNAME	(2)	/* name */
#define SPCOM	(3)	/* comment */
#define SPPRAGMA (4)	/* pragma */
#define SPRINTX (5)	/* printx */


#line 1926 "zmac.y"
typedef union	{
	struct expr *exprptr;
	struct item *itemptr;
	int ival;
	char *cval;
	} YYSTYPE;
#line 2073 "zmac.y"

char  *cp;
int  i;

void do_equ(struct item *sym, struct expr *val, int call_list)
{
	expr_reloc_check(val);
	switch(sym->i_token) {
	case UNDECLARED: case WASEQUATED:
		if (sym->i_token == WASEQUATED &&
			(sym->i_value != val->e_value ||
			 ((sym->i_scope ^ val->e_scope) & SCOPE_SEGMASK)))
		{
			if (outpass) {
				if (sym->i_value != val->e_value)
					sprintf(detail, "%s error - %s went from $%04x to $%04x",
						errname[pflag], sym->i_string, sym->i_value, val->e_value);
				else
					sprintf(detail, "%s error - %s changed scope",
						errname[pflag], sym->i_string);
				errwarn(pflag, detail);
			}
			else
				passretry = 1;
		}

		sym->i_token = EQUATED;
		sym->i_pass = npass;
		sym->i_value = val->e_value;
		sym->i_scope |= val->e_scope;
		break;
	default:
		// m80 allows multiple equates as long as the value
		// does not change.  So does newer zmac.
		if (sym->i_value != val->e_value ||
			((sym->i_scope ^ val->e_scope) & SCOPE_SEGMASK))
		{
			err[mflag]++;
			sym->i_token = MULTDEF;
			sym->i_pass = npass;
		}
	}
	sym->i_scope &= ~SCOPE_BUILTIN;
	if (call_list)
		list(val->e_value);
	expr_free(val);
}

void do_defl(struct item *sym, struct expr *val, int call_list)
{
	expr_reloc_check(val);
	switch(sym->i_token) {
	case UNDECLARED: case DEFLED:
		sym->i_token = DEFLED;
		sym->i_pass = npass;
		sym->i_value = val->e_value;
		sym->i_scope = (sym->i_scope & SCOPE_SEGMASK) | val->e_scope;
		break;
	default:
		err[mflag]++;
		sym->i_token = MULTDEF;
		sym->i_pass = npass;
		break;
	}
	if (call_list)
		list(val->e_value);
	expr_free(val);
}

void do_end(struct expr *entry)
{
	if (entry) {
		expr_reloc_check(entry);
		xeq_flag++;
		xeq = entry->e_value & 0xffff;
		rel_main = ((entry->e_scope & SCOPE_SEGMASK) << 16) | xeq;
		expr_free(entry);
	}

// TODO - no reason no to treat END as a simple mras or not.
// At least, give this a try and see how it goes.
//	if (mras) {
		while (expptr)
			popsi();

		peekc = NOPEEK;
		nextline_peek = EOF;
//	}
//	else
//		peekc = 0;

}

void do_if_value(int value)
{
	char saveopt;

	if (ifptr >= ifstmax)
		error("Too many ifs");
	else
		*++ifptr = !(value);

	saveopt = fopt;
	fopt = 1;
	list(value);
	fopt = saveopt;
}

void do_if(struct expr *expr)
{
	expr_number_check(expr);
	do_if_value(expr->e_value);
	expr_free(expr);
}

void common_block(char *unparsed_id)
{
	struct item *it;
	char *id = unparsed_id;
	char *p;
	int unnamed;

	if (*id == '/') {
		id++;
		for (p = id; *p; p++)
			if (*p == '/')
				*p = '\0';
	}

	unnamed = 1;
	for (p = id; *p; p++)
		if (*p != ' ')
			unnamed = 0;

	id = unnamed ? " " : id;

	it = locate(id);
	switch (it->i_token) {
	case 0:
		nitems++;
	case UNDECLARED:
	case COMMON:
		it->i_value = 0;
		it->i_token = COMMON;
		it->i_pass = npass;
		it->i_scope = SCOPE_COMBLOCK;
		it->i_uses = 0;
		if (!it->i_string)
			it->i_string = strdup(id);
		break;
	default:
		err[mflag]++;
		it->i_token = MULTDEF;
		it->i_pass = npass;
			it->i_string = strdup(id);
		break;
	}

	// Even if we change to the same COMMON block the address is
	// reset back to 0.
	if (relopt) {
		segment = SEG_COMMON;
		segchange = 1;
		dollarsign = seg_pos[SEG_COMMON] = seg_size[SEG_COMMON] = 0;
		// May not be necessary but too much trouble to suppress.
		putrelcmd(RELCMD_COMMON);
		putrelname(it->i_string);
	}

	cur_common = it;
}

int at_least_once; // global to avoid repetition in macro repeat count processing

void dolopt(struct item *itm, int enable)
{
	if (outpass) {
		lineptr = linebuf;
		switch (itm->i_value) {
		case 0:	/* list */
			if (enable < 0) lstoff = 1;
			if (enable > 0) lstoff = 0;
			break;

		case 1:	/* eject */
			if (enable) eject();
			break;

		case 2:	/* space */
			if ((line + enable) > 60) eject();
			else space(enable);
			break;

		case 3:	/* elist */
			eopt = edef;
			if (enable < 0) eopt = 0;
			if (enable > 0) eopt = 1;
			break;

		case 4:	/* fopt */
			fopt = fdef;
			if (enable < 0) fopt = 0;
			if (enable > 0) fopt = 1;
			break;

		case 5:	/* gopt */
			gopt = gdef;
			if (enable < 0) gopt = 1;
			if (enable > 0) gopt = 0;
			break;

		case 6: /* mopt */
			mopt = mdef;
			if (enable < 0) mopt = 0;
			if (enable > 0) mopt = 1;
		}
	}
}

#include <stdio.h>

#ifndef __cplusplus
#ifndef __STDC__
#define const
#endif
#endif



#define	YYFINAL		714
#define	YYFLAG		-32768
#define	YYNTBASE	193

#define YYTRANSLATE(x) ((unsigned)(x) <= 423 ? yytranslate[x] : 268)

static const short yytranslate[] = {     0,
     2,     2,     2,     2,     2,     2,     2,     2,     2,   185,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,   182,     2,   189,   190,   181,   172,     2,   187,
   188,   179,   177,   186,   178,     2,   180,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,   169,     2,   174,
   173,   175,   168,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
   191,     2,   192,   171,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,   170,     2,   183,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     1,     3,     4,     5,     6,
     7,     8,     9,    10,    11,    12,    13,    14,    15,    16,
    17,    18,    19,    20,    21,    22,    23,    24,    25,    26,
    27,    28,    29,    30,    31,    32,    33,    34,    35,    36,
    37,    38,    39,    40,    41,    42,    43,    44,    45,    46,
    47,    48,    49,    50,    51,    52,    53,    54,    55,    56,
    57,    58,    59,    60,    61,    62,    63,    64,    65,    66,
    67,    68,    69,    70,    71,    72,    73,    74,    75,    76,
    77,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    95,    96,
    97,    98,    99,   100,   101,   102,   103,   104,   105,   106,
   107,   108,   109,   110,   111,   112,   113,   114,   115,   116,
   117,   118,   119,   120,   121,   122,   123,   124,   125,   126,
   127,   128,   129,   130,   131,   132,   133,   134,   135,   136,
   137,   138,   139,   140,   141,   142,   143,   144,   145,   146,
   147,   148,   149,   150,   151,   152,   153,   154,   155,   156,
   157,   158,   159,   160,   161,   162,   163,   164,   165,   166,
   167,   176,   184
};

#if YYDEBUG != 0
static const short yyprhs[] = {     0,
     0,     1,     4,     7,     8,    13,    19,    25,    31,    36,
    42,    47,    52,    59,    63,    67,    70,    73,    79,    85,
    88,    91,    95,   100,   105,   112,   117,   122,   127,   134,
   141,   147,   154,   155,   159,   162,   168,   172,   176,   180,
   184,   187,   191,   194,   195,   196,   204,   205,   212,   213,
   221,   222,   223,   235,   236,   237,   249,   253,   256,   259,
   262,   264,   265,   267,   270,   271,   274,   276,   280,   282,
   284,   288,   290,   292,   294,   296,   298,   300,   302,   304,
   306,   308,   310,   312,   314,   316,   318,   320,   322,   324,
   326,   328,   330,   332,   334,   336,   338,   341,   343,   346,
   349,   352,   355,   358,   361,   366,   369,   374,   377,   380,
   383,   386,   389,   394,   399,   404,   409,   412,   417,   420,
   423,   428,   431,   434,   437,   440,   443,   446,   449,   454,
   459,   464,   469,   472,   475,   480,   483,   486,   491,   496,
   501,   504,   507,   510,   513,   516,   519,   522,   525,   528,
   533,   538,   545,   550,   553,   558,   561,   566,   569,   572,
   577,   580,   583,   585,   588,   593,   598,   603,   608,   613,
   618,   623,   630,   633,   638,   641,   648,   651,   656,   659,
   664,   669,   674,   679,   684,   687,   692,   695,   700,   703,
   708,   713,   720,   725,   730,   733,   736,   743,   746,   753,
   758,   763,   768,   771,   778,   781,   788,   791,   794,   797,
   799,   802,   805,   808,   811,   812,   816,   817,   821,   822,
   826,   827,   831,   833,   834,   836,   840,   841,   844,   845,
   847,   850,   852,   853,   854,   860,   861,   863,   867,   869,
   870,   872,   876,   878,   879,   883,   885,   887,   889,   891,
   893,   895,   897,   899,   901,   903,   905,   909,   911,   916,
   920,   925,   927,   929,   931,   933,   935,   937,   939,   941,
   943,   945,   947,   949,   951,   953,   955,   957,   959,   961,
   963,   965,   967,   969,   971,   973,   975,   977,   979,   981,
   983,   985,   987,   989,   991,   993,   997,   999,  1001,  1003,
  1007,  1009,  1011,  1015,  1017,  1019,  1023,  1025,  1027,  1029,
  1033,  1035,  1037,  1039,  1041,  1043,  1045,  1047,  1049,  1051,
  1053,  1055,  1056,  1060,  1064,  1068,  1072,  1076,  1080,  1084,
  1088,  1092,  1096,  1100,  1104,  1108,  1112,  1116,  1120,  1124,
  1128,  1132,  1136,  1140,  1144,  1148,  1152,  1156,  1160,  1164,
  1168,  1172,  1176,  1180,  1184,  1188,  1192,  1196,  1200,  1204,
  1208,  1212,  1216,  1220,  1224,  1230,  1234,  1237,  1240,  1243,
  1246,  1249,  1252,  1255,  1258,  1261,  1264,  1267,  1270,  1273,
  1276,  1279,  1281,  1283,  1285,  1287,  1289,  1291,  1293,  1294,
  1295,  1296,  1297
};

static const short yyrhs[] = {    -1,
   193,   194,     0,   206,   185,     0,     0,   206,   195,   212,
   185,     0,   262,   205,    62,   258,   185,     0,   262,   205,
    62,   247,   185,     0,   262,   205,   173,   258,   185,     0,
   262,    63,   258,   185,     0,   262,   211,   173,   258,   185,
     0,   262,   177,   177,   185,     0,   262,   178,   178,   185,
     0,   262,   109,   258,   186,   258,   185,     0,    98,   258,
   185,     0,    99,   258,   185,     0,   100,   185,     0,   101,
   185,     0,   103,   258,   186,   258,   185,     0,   102,   264,
   112,   265,   185,     0,   104,   185,     0,   105,   185,     0,
   206,    45,   185,     0,   206,    45,   258,   185,     0,   206,
    59,   258,   185,     0,   206,    59,   258,   186,   258,   185,
     0,   206,    56,   114,   185,     0,   206,    56,   115,   185,
     0,   206,    56,     3,   185,     0,   206,    56,   258,   186,
   258,   185,     0,   206,   106,   264,   112,   265,   185,     0,
   206,   106,   264,   265,   185,     0,   206,   107,   264,   112,
   265,   185,     0,     0,   140,   196,   141,     0,   108,   185,
     0,   108,   266,   258,   267,   185,     0,   116,   258,   185,
     0,   117,   258,   185,     0,   118,   207,   185,     0,   119,
   209,   185,     0,   120,   185,     0,   206,   121,   185,     0,
   122,   185,     0,     0,     0,    44,   110,   197,   217,   185,
   198,   222,     0,     0,   206,   111,   263,   199,   227,   185,
     0,     0,   206,   154,   258,   263,   185,   200,   222,     0,
     0,     0,   206,   155,   218,   186,   201,   263,   228,   265,
   185,   202,   222,     0,     0,     0,   206,   156,   218,   186,
   203,   263,   228,   265,   185,   204,   222,     0,   206,   157,
   185,     0,   165,   185,     0,   166,   185,     0,   167,   185,
     0,     1,     0,     0,   169,     0,   169,   169,     0,     0,
   262,   205,     0,   208,     0,   207,   186,   208,     0,   262,
     0,   210,     0,   209,   186,   210,     0,   262,     0,   177,
     0,   178,     0,   179,     0,   180,     0,   181,     0,   172,
     0,   170,     0,   171,     0,    11,     0,    12,     0,    70,
     0,    71,     0,    78,     0,    79,     0,    80,     0,    81,
     0,    82,     0,    83,     0,    84,     0,    85,     0,    93,
     0,    94,     0,    92,     0,     4,     0,     4,   258,     0,
    27,     0,   137,   258,     0,    14,   258,     0,    28,   258,
     0,   139,   258,     0,   146,   238,     0,     6,   258,     0,
     6,    31,   186,   258,     0,     5,   258,     0,     5,    31,
   186,   258,     0,     7,   258,     0,     8,   258,     0,     9,
   258,     0,    10,   258,     0,   163,   258,     0,     7,    31,
   186,   258,     0,     8,    31,   186,   258,     0,     9,    31,
   186,   258,     0,    10,    31,   186,   258,     0,     6,   230,
     0,     6,    31,   186,   230,     0,     6,   234,     0,     5,
   230,     0,     5,    31,   186,   230,     0,     5,   234,     0,
     7,   230,     0,     7,   234,     0,     8,   230,     0,     9,
   230,     0,    10,   230,     0,   163,   231,     0,     7,    31,
   186,   230,     0,     8,    31,   186,   230,     0,     9,    31,
   186,   230,     0,    10,    31,   186,   230,     0,    27,   231,
     0,   148,   238,     0,    27,   237,   186,   235,     0,    15,
   230,     0,   134,   233,     0,     5,    34,   186,   244,     0,
     6,   246,   186,   243,     0,     6,   246,   186,   246,     0,
   124,   240,     0,   153,   243,     0,   153,   246,     0,    15,
   239,     0,   133,   240,     0,   162,   245,     0,    25,   241,
     0,    25,   242,     0,    13,   258,     0,    13,   258,   186,
   231,     0,   147,   258,   186,   238,     0,    13,   258,   186,
   237,   186,   235,     0,   137,   248,   186,   258,     0,   136,
   258,     0,   137,   187,   246,   188,     0,   137,   246,     0,
    14,   248,   186,   258,     0,   138,   258,     0,    22,   258,
     0,    22,   249,   186,   258,     0,   151,   258,     0,    16,
   258,     0,    26,     0,    26,   248,     0,    23,   230,   186,
   230,     0,   143,   235,   186,   238,     0,   144,   235,   186,
   238,     0,   132,   233,   186,   233,     0,    23,   230,   186,
   260,     0,   145,   258,   186,   238,     0,   131,   233,   186,
   258,     0,    23,   230,   186,   187,    33,   188,     0,   128,
   235,     0,    23,   230,   186,   259,     0,   130,   258,     0,
    23,   187,    33,   188,   186,    31,     0,   125,   235,     0,
    23,   259,   186,    31,     0,   126,   258,     0,    23,   230,
   186,    40,     0,    23,    40,   186,    31,     0,    23,   239,
   186,   260,     0,   123,   240,   186,   258,     0,    23,   239,
   186,   259,     0,   129,   258,     0,    23,   259,   186,   239,
     0,   127,   258,     0,    23,   239,   186,   246,     0,   152,
   258,     0,    17,    33,   186,    34,     0,    17,    36,   186,
    38,     0,    17,   187,    39,   188,   186,   246,     0,    21,
   235,   186,   259,     0,   160,   235,   186,   259,     0,   160,
   259,     0,    21,   258,     0,    21,   235,   186,   187,    32,
   188,     0,   149,   235,     0,    21,    37,   186,   187,    32,
   188,     0,    21,   187,    32,   188,     0,    24,   259,   186,
    31,     0,   161,   259,   186,   235,     0,    24,   258,     0,
    24,   187,    32,   188,   186,   235,     0,   150,   235,     0,
    24,   187,    32,   188,   186,   258,     0,   164,   259,     0,
    18,   258,     0,    19,   258,     0,    20,     0,    46,   258,
     0,    47,   258,     0,    48,   258,     0,    52,   258,     0,
     0,    57,   213,   250,     0,     0,    60,   214,   252,     0,
     0,    61,   215,   254,     0,     0,    58,   216,   256,     0,
   113,     0,     0,   221,     0,   217,   186,   221,     0,     0,
   219,   221,     0,     0,   189,     0,   220,   159,     0,   223,
     0,     0,     0,   223,   142,   224,   225,   185,     0,     0,
   226,     0,   225,   186,   226,     0,   159,     0,     0,   228,
     0,   227,   186,   228,     0,   112,     0,     0,   181,   229,
   258,     0,   231,     0,   232,     0,   235,     0,   236,     0,
    30,     0,   235,     0,   234,     0,    41,     0,    29,     0,
    31,     0,    32,     0,   187,    34,   188,     0,   237,     0,
   187,    35,   238,   188,     0,   187,    35,   188,     0,   238,
   187,    35,   188,     0,   258,     0,   243,     0,   246,     0,
   235,     0,    39,     0,    33,     0,    36,     0,    38,     0,
   246,     0,   235,     0,   135,     0,    33,     0,    39,     0,
   243,     0,    34,     0,    33,     0,    34,     0,    34,     0,
    35,     0,    29,     0,    31,     0,    32,     0,    36,     0,
   135,     0,    33,     0,    34,     0,    35,     0,    39,     0,
    41,     0,   249,     0,    41,     0,    42,     0,    32,     0,
   251,     0,   250,   186,   251,     0,     3,     0,   258,     0,
   253,     0,   252,   186,   253,     0,   258,     0,   255,     0,
   254,   186,   255,     0,   258,     0,   257,     0,   256,   186,
   257,     0,   258,     0,   259,     0,   260,     0,   187,   258,
   188,     0,    64,     0,    43,     0,   114,     0,   115,     0,
    65,     0,    66,     0,    67,     0,    68,     0,   190,     0,
    44,     0,    69,     0,     0,   158,   261,   141,     0,   258,
   177,   258,     0,   258,   178,   258,     0,   258,   180,   258,
     0,   258,   179,   258,     0,   258,   181,   258,     0,   258,
   172,   258,     0,   258,     8,   258,     0,   258,   170,   258,
     0,   258,     9,   258,     0,   258,   171,   258,     0,   258,
    10,   258,     0,   258,    70,   258,     0,   258,    71,   258,
     0,   258,   174,   258,     0,   258,    72,   258,     0,   258,
   173,   258,     0,   258,    73,   258,     0,   258,   175,   258,
     0,   258,   176,   258,     0,   258,    74,   258,     0,   258,
    76,   258,     0,   258,    75,   258,     0,   258,    11,   258,
     0,   258,    12,   258,     0,   258,    78,   258,     0,   258,
    79,   258,     0,   258,    81,   258,     0,   258,    80,   258,
     0,   258,    82,   258,     0,   258,    83,   258,     0,   258,
    84,   258,     0,   258,    85,   258,     0,   258,    93,   258,
     0,   258,    94,   258,     0,   258,    88,   258,     0,   258,
    87,   258,     0,   258,    89,   258,     0,   258,    90,   258,
     0,   258,    86,   258,     0,   258,    91,   258,     0,   258,
    92,   258,     0,   258,   168,   258,   169,   258,     0,   191,
   258,   192,     0,   183,   258,     0,    95,   258,     0,   182,
   258,     0,   177,   258,     0,    78,   258,     0,   178,   258,
     0,    79,   258,     0,    49,   258,     0,    50,   258,     0,
    51,   258,     0,    53,   258,     0,    54,   258,     0,    96,
   258,     0,    55,   258,     0,    97,   258,     0,    44,     0,
    64,     0,    69,     0,    65,     0,    66,     0,    67,     0,
    68,     0,     0,     0,     0,     0,     0
};

#endif

#if YYDEBUG != 0
static const short yyrline[] = { 0,
  2296,  2298,  2303,  2320,  2321,  2324,  2330,  2337,  2346,  2350,
  2354,  2358,  2362,  2387,  2391,  2397,  2401,  2405,  2410,  2418,
  2429,  2435,  2440,  2445,  2470,  2485,  2487,  2489,  2500,  2509,
  2561,  2572,  2576,  2577,  2648,  2651,  2676,  2683,  2690,  2694,
  2698,  2709,  2718,  2723,  2724,  2740,  2747,  2748,  2769,  2783,
  2803,  2804,  2813,  2838,  2839,  2850,  2886,  2894,  2899,  2904,
  2909,  2937,  2939,  2941,  2945,  2948,  3003,  3005,  3009,  3023,
  3025,  3029,  3046,  3047,  3048,  3049,  3050,  3051,  3052,  3053,
  3054,  3055,  3056,  3057,  3058,  3060,  3061,  3062,  3063,  3064,
  3065,  3066,  3067,  3068,  3069,  3073,  3076,  3085,  3093,  3107,
  3110,  3122,  3125,  3130,  3133,  3136,  3139,  3142,  3151,  3154,
  3157,  3160,  3163,  3166,  3169,  3172,  3175,  3178,  3181,  3184,
  3187,  3190,  3193,  3196,  3199,  3202,  3205,  3208,  3211,  3214,
  3217,  3220,  3223,  3226,  3231,  3234,  3237,  3240,  3247,  3250,
  3259,  3261,  3266,  3284,  3287,  3290,  3293,  3296,  3299,  3314,
  3324,  3335,  3345,  3351,  3357,  3360,  3363,  3366,  3369,  3372,
  3375,  3378,  3381,  3384,  3387,  3418,  3423,  3428,  3434,  3437,
  3442,  3445,  3453,  3459,  3471,  3477,  3480,  3486,  3492,  3498,
  3507,  3510,  3516,  3522,  3531,  3537,  3546,  3552,  3562,  3568,
  3578,  3581,  3584,  3597,  3605,  3613,  3620,  3623,  3626,  3629,
  3632,  3639,  3647,  3654,  3657,  3660,  3672,  3680,  3691,  3705,
  3715,  3750,  3762,  3772,  3782,  3783,  3784,  3785,  3786,  3787,
  3788,  3789,  3790,  3794,  3795,  3797,  3801,  3801,  3803,  3803,
  3805,  3816,  3830,  3831,  3832,  3835,  3836,  3838,  3842,  3853,
  3855,  3857,  3862,  3872,  3874,  3883,  3885,  3888,  3890,  3893,
  3899,  3901,  3904,  3907,  3912,  3917,  3923,  3928,  3931,  3936,
  3942,  3948,  3957,  3959,  3962,  3964,  3967,  3972,  3977,  3982,
  3985,  3987,  3990,  3995,  4001,  4003,  4009,  4014,  4020,  4025,
  4031,  4031,  4031,  4031,  4031,  4031,  4031,  4031,  4031,  4031,
  4033,  4035,  4041,  4046,  4050,  4052,  4055,  4062,  4081,  4083,
  4088,  4098,  4100,  4105,  4115,  4117,  4122,  4130,  4132,  4136,
  4141,  4159,  4164,  4169,  4176,  4181,  4186,  4191,  4196,  4202,
  4231,  4243,  4245,  4248,  4249,  4250,  4251,  4252,  4253,  4254,
  4255,  4256,  4257,  4258,  4259,  4260,  4261,  4262,  4263,  4264,
  4265,  4266,  4267,  4268,  4269,  4270,  4271,  4273,  4274,  4275,
  4276,  4277,  4278,  4279,  4280,  4281,  4282,  4283,  4284,  4285,
  4286,  4287,  4288,  4289,  4299,  4313,  4316,  4319,  4322,  4325,
  4328,  4331,  4334,  4337,  4344,  4353,  4362,  4369,  4374,  4379,
  4384,  4391,  4393,  4395,  4397,  4399,  4401,  4403,  4408,  4421,
  4425,  4429,  4433
};
#endif


#if YYDEBUG != 0 || defined (YYERROR_VERBOSE)

static const char * const yytname[] = {   "$","error","$undefined.","STRING",
"NOOPERAND","ARITHC","ADD","LOGICAL","AND","OR","XOR","ANDAND","OROR","BIT",
"CALL","INCDEC","DJNZ","EX","IM","PHASE","DEPHASE","TK_IN","JR","LD","TK_OUT",
"PUSHPOP","RET","SHIFT","RST","REGNAME","IXYLH","ACC","TK_C","RP","HL","INDEX",
"AF","TK_F","AFp","SP","MISCREG","COND","SPCOND","NUMBER","UNDECLARED","END",
"ORG","ASSERT","TSTATE","T","TILO","TIHI","SETOCF","OCF","LOW","HIGH","DC","DEFB",
"DEFD","DEFS","DEFW","DEF3","EQU","DEFL","LABEL","EQUATED","WASEQUATED","DEFLED",
"COMMON","MULTDEF","SHL","SHR","LT","EQ","LE","GE","NE","NOT","MROP_ADD","MROP_SUB",
"MROP_MUL","MROP_DIV","MROP_MOD","MROP_AND","MROP_OR","MROP_XOR","MROP_NE","MROP_EQ",
"MROP_LT","MROP_GT","MROP_LE","MROP_GE","MROP_SHIFT","MROP_SHL","MROP_SHR","MROP_NOT",
"MROP_LOW","MROP_HIGH","IF_TK","IFE_TK","IF1_TK","IF2_TK","IF_DEF_TK","IF_CP_TK",
"ELSE_TK","ENDIF_TK","ARGPSEUDO","INCBIN","LIST","MINMAX","MACRO","MNAME","ARG",
"ENDM","ONECHAR","TWOCHAR","JRPROMOTE","JPERROR","PUBLIC","EXTRN","MRAS_MOD",
"SETSEG","INSTSET","LXI","DAD","STAX","STA","SHLD","LDAX","LHLD","LDA","MVI",
"MOV","INXDCX","INRDCR","PSW","JUMP8","JP","CALL8","ALUI8","SPECIAL","RAWTOKEN",
"LOCAL","LD_XY","ST_XY","MV_XY","ALU_XY","BIT_XY","SHIFT_XY","INP","OUTP","JR_COND",
"LDST16","ARITH16","REPT","IRPC","IRP","EXITM","NUL","MPARM","TK_IN0","TK_OUT0",
"MLT","TST","TSTIO","LALL","SALL","XALL","'?'","':'","'|'","'^'","'&'","'='",
"'<'","'>'","GT","'+'","'-'","'*'","'/'","'%'","'!'","'~'","UNARY","'\\n'","','",
"'('","')'","'#'","'$'","'['","']'","statements","statement","@1","@2","@3",
"@4","@5","@6","@7","@8","@9","@10","maybecolon","label.part","public.list",
"public.part","extrn.list","extrn.part","varop","operation","@11","@12","@13",
"@14","parm.list","parm.single","@15","maybeocto","parm.element","locals","local_decls",
"@16","local.list","local.element","arg.list","arg.element","@17","allreg","reg",
"ixylhreg","reg8","m","realreg","mem","memxy","dxy","evenreg","evenreg8","pushable",
"pushable8","bcdesp","bcdehlsp","bcdehl","mar","aliasable","condition","spcondition",
"db.list","db.list.element","dw.list","dw.list.element","d3.list","d3.list.element",
"dd.list","dd.list.element","expression","parenexpr","noparenexpr","@18","symbol",
"al","arg_on","arg_off","mras_undecl_on","mras_undecl_off", NULL
};
#endif

static const short yyr1[] = {     0,
   193,   193,   194,   195,   194,   194,   194,   194,   194,   194,
   194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
   194,   194,   194,   194,   194,   194,   194,   194,   194,   194,
   194,   194,   196,   194,   194,   194,   194,   194,   194,   194,
   194,   194,   194,   197,   198,   194,   199,   194,   200,   194,
   201,   202,   194,   203,   204,   194,   194,   194,   194,   194,
   194,   205,   205,   205,   206,   206,   207,   207,   208,   209,
   209,   210,   211,   211,   211,   211,   211,   211,   211,   211,
   211,   211,   211,   211,   211,   211,   211,   211,   211,   211,
   211,   211,   211,   211,   211,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   212,   212,   212,   212,   212,   212,
   212,   212,   212,   212,   213,   212,   214,   212,   215,   212,
   216,   212,   212,   217,   217,   217,   219,   218,   220,   220,
   221,   222,   223,   224,   223,   225,   225,   225,   226,   227,
   227,   227,   228,   229,   228,   230,   230,   231,   231,   232,
   233,   233,   234,   235,   235,   235,   236,   236,   237,   237,
   237,   238,   239,   239,   240,   240,   241,   241,   241,   241,
   242,   242,   243,   243,   244,   244,   245,   245,   246,   246,
   247,   247,   247,   247,   247,   247,   247,   247,   247,   247,
   248,   248,   249,   249,   250,   250,   251,   251,   252,   252,
   253,   254,   254,   255,   256,   256,   257,   258,   258,   259,
   260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
   260,   261,   260,   260,   260,   260,   260,   260,   260,   260,
   260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
   260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
   260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
   260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
   260,   260,   260,   260,   260,   260,   260,   260,   260,   260,
   260,   262,   262,   262,   262,   262,   262,   262,   263,   264,
   265,   266,   267
};

static const short yyr2[] = {     0,
     0,     2,     2,     0,     4,     5,     5,     5,     4,     5,
     4,     4,     6,     3,     3,     2,     2,     5,     5,     2,
     2,     3,     4,     4,     6,     4,     4,     4,     6,     6,
     5,     6,     0,     3,     2,     5,     3,     3,     3,     3,
     2,     3,     2,     0,     0,     7,     0,     6,     0,     7,
     0,     0,    11,     0,     0,    11,     3,     2,     2,     2,
     1,     0,     1,     2,     0,     2,     1,     3,     1,     1,
     3,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     2,     1,     2,     2,
     2,     2,     2,     2,     4,     2,     4,     2,     2,     2,
     2,     2,     4,     4,     4,     4,     2,     4,     2,     2,
     4,     2,     2,     2,     2,     2,     2,     2,     4,     4,
     4,     4,     2,     2,     4,     2,     2,     4,     4,     4,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     4,
     4,     6,     4,     2,     4,     2,     4,     2,     2,     4,
     2,     2,     1,     2,     4,     4,     4,     4,     4,     4,
     4,     6,     2,     4,     2,     6,     2,     4,     2,     4,
     4,     4,     4,     4,     2,     4,     2,     4,     2,     4,
     4,     6,     4,     4,     2,     2,     6,     2,     6,     4,
     4,     4,     2,     6,     2,     6,     2,     2,     2,     1,
     2,     2,     2,     2,     0,     3,     0,     3,     0,     3,
     0,     3,     1,     0,     1,     3,     0,     2,     0,     1,
     2,     1,     0,     0,     5,     0,     1,     3,     1,     0,
     1,     3,     1,     0,     3,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     3,     1,     4,     3,
     4,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     1,     1,     1,     1,     3,     1,     1,     1,     3,
     1,     1,     3,     1,     1,     3,     1,     1,     1,     3,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
     1,     0,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     3,     3,     3,     3,     3,     3,
     3,     3,     3,     3,     5,     3,     2,     2,     2,     2,
     2,     2,     2,     2,     2,     2,     2,     2,     2,     2,
     2,     1,     1,     1,     1,     1,     1,     1,     0,     0,
     0,     0,     0
};

static const short yydefact[] = {     1,
     0,    61,   382,   383,   385,   386,   387,   388,   384,     0,
     0,     0,     0,   390,     0,     0,     0,   392,     0,     0,
     0,     0,     0,     0,    33,     0,     0,     0,     2,     4,
    62,    44,   312,   320,     0,     0,     0,     0,     0,     0,
   311,   315,   316,   317,   318,   321,     0,     0,     0,     0,
     0,   313,   314,   322,     0,     0,     0,     0,     0,   319,
     0,     0,   308,   309,     0,    16,    17,     0,     0,    20,
    21,    35,     0,     0,     0,   382,     0,    67,    69,     0,
    70,    72,    41,    43,     0,    58,    59,    60,     0,     0,
     0,   390,   390,   389,     0,     0,   227,   227,     0,     3,
     0,    81,    82,     0,    83,    84,    85,    86,    87,    88,
    89,    90,    91,    92,    95,    93,    94,     0,    63,    79,
    80,    78,    73,    74,    75,    76,    77,    66,     0,   224,
   374,   375,   376,   377,   378,   380,   371,   373,   368,   379,
   381,     0,   370,   372,   369,   367,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    14,    15,   391,     0,   393,    37,    38,    39,     0,    40,
     0,    34,    22,     0,     0,   313,   314,     0,     0,   391,
     0,    47,    42,   389,     0,   229,     0,    57,    96,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   210,     0,     0,     0,     0,     0,   163,    98,
     0,     0,     0,     0,     0,   215,   221,   217,   219,   223,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    64,     0,     0,     0,     0,
     0,   230,     0,     0,   225,   323,   310,   366,   330,   332,
   334,   346,   347,   335,   336,   338,   340,   343,   345,   344,
   348,   349,   351,   350,   352,   353,   354,   355,   362,   359,
   358,   360,   361,   363,   364,   356,   357,     0,   331,   333,
   329,   339,   337,   341,   342,   324,   325,   327,   326,   328,
     0,     0,     0,    68,    71,    23,    28,    26,    27,     0,
    24,     0,   391,     0,   391,   240,     0,    51,   228,    54,
    97,   254,   250,   255,   256,     0,   253,     0,   120,   246,
   247,   122,   248,   249,   258,     0,   106,   255,   279,   280,
   117,   119,     0,   104,   255,   123,   124,   108,   255,   125,
   109,   255,   126,   110,   255,   127,   111,   149,   294,   292,
   293,     0,   291,   100,   255,   273,   274,   136,   144,   263,
   264,   262,   162,     0,     0,     0,   208,   209,     0,     0,
     0,   196,     0,   159,     0,     0,     0,     0,   308,     0,
   203,   308,   267,   268,   269,   272,   271,   147,   148,   270,
   164,   133,   258,   101,   211,   212,   213,   214,     0,     0,
     0,     0,   266,   265,     0,   141,   177,   179,   187,   173,
   185,   175,     0,   252,   251,     0,   145,   137,   154,     0,
   156,     0,    99,   158,   102,     0,     0,     0,   103,     0,
   134,   198,   205,   161,   189,   142,   143,     0,   195,     0,
   277,   278,   146,   128,   112,   207,     5,     9,     0,    11,
    12,   281,   282,   283,   286,   287,   288,   284,   289,   290,
   285,     0,     0,     0,     0,    45,   229,   231,     0,    19,
    18,    36,     0,     0,     0,    31,     0,   243,   244,     0,
   241,    49,   389,   389,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   297,   216,   295,   298,   222,   305,   307,   218,
   299,   301,   220,   302,   304,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     7,     6,     8,
    10,   233,   226,   365,    29,    25,    30,    32,     0,    48,
     0,   233,     0,     0,   121,   107,   276,   275,   138,   257,
   260,     0,     0,   118,   105,   139,   140,   129,   113,   130,
   114,   131,   115,   132,   116,   150,   258,   157,   190,   191,
     0,     0,   200,     0,   193,   160,   181,     0,   180,     0,
   165,   308,   309,   188,     0,   308,   309,   178,   186,     0,
   201,   135,     0,     0,     0,     0,   183,   171,   168,   155,
   153,   166,   167,   170,   151,   194,   202,    13,    46,   232,
   245,   242,    50,   391,   391,   259,   261,     0,     0,     0,
     0,     0,     0,     0,   296,   306,   300,   303,   234,     0,
     0,   152,   192,   199,   197,   176,   172,   204,   206,   236,
    52,    55,   239,     0,   237,   233,   233,   235,     0,    53,
    56,   238,     0,     0
};

static const short yydefgoto[] = {     1,
    29,   101,    85,   130,   592,   356,   602,   533,   706,   534,
   707,   128,    30,    77,    78,    80,    81,   129,   283,   449,
   451,   452,   450,   293,   215,   216,   294,   295,   669,   670,
   700,   704,   705,   530,   531,   599,   369,   370,   371,   463,
   464,   373,   374,   375,   376,   409,   455,   438,   439,   410,
   609,   493,   411,   512,   402,   403,   564,   565,   570,   571,
   573,   574,   567,   568,   412,    63,    64,   142,    79,   212,
    68,   341,    73,   343
};

static const short yypact[] = {-32768,
   686,-32768,   -91,-32768,-32768,-32768,-32768,-32768,-32768,  5010,
  5010,  -164,  -152,-32768,  5010,  -142,  -130,  -125,  5010,  5010,
    68,    68,  -116,  -102,-32768,   -98,   -82,   -78,-32768,   239,
  2500,-32768,-32768,-32768,  5010,  5010,  5010,  5010,  5010,  5010,
-32768,-32768,-32768,-32768,-32768,-32768,  5010,  5010,  5010,  5010,
  5010,-32768,-32768,-32768,  5010,  5010,  5010,  5010,  5010,-32768,
  5010,  1403,-32768,-32768,  1428,-32768,-32768,   -17,  1045,-32768,
-32768,-32768,  5010,  1557,  1582,-32768,     9,-32768,-32768,    16,
-32768,-32768,-32768,-32768,   -32,-32768,-32768,-32768,  4827,   432,
  5010,-32768,-32768,-32768,   -72,  5010,-32768,-32768,   -67,-32768,
  3879,-32768,-32768,  5010,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,  5010,   -48,-32768,
-32768,-32768,   -47,   -40,-32768,-32768,-32768,   -50,     8,  -135,
   365,   365,   365,   365,   365,   365,-32768,-32768,-32768,-32768,
-32768,    45,   365,   365,   365,   365,   871,   846,  5010,  5010,
  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,
  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,
  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,
  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,  5010,
-32768,-32768,-32768,  5010,  2269,-32768,-32768,-32768,    68,-32768,
    68,-32768,-32768,  1607,    18,    33,    41,  1070,  1020,    88,
   108,-32768,-32768,  2269,    60,    63,    74,-32768,  5010,  3003,
  2906,  3081,  3252,  3349,  3423,  5010,  4042,  2828,  5010,    17,
  5010,  5010,-32768,  3520,  4081,  2731,  5155,    93,    36,  3691,
  5010,  5010,  5010,  5010,  5010,-32768,-32768,-32768,-32768,-32768,
    53,    53,    85,  5010,  5010,    85,  5010,  5010,    35,    35,
    53,    35,  5010,  4003,  5010,  5010,    85,    85,  5010,  5010,
  5010,  5010,    85,    85,  5010,  5010,    67,     3,    75,   172,
  3691,    75,    79,  1735,  1199,-32768,    84,    89,  2653,  5010,
  5010,-32768,    44,   111,-32768,-32768,-32768,-32768,  5201,  2443,
  2468,  2319,  2294,   288,   288,  3883,  5236,  3883,  3883,  5236,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,  2141,  2443,  2468,
  5201,  5236,  3883,  3883,  3883,  1087,  1087,   365,   365,   365,
    90,  1760,    91,-32768,-32768,-32768,-32768,-32768,-32768,  5010,
-32768,  5010,-32768,    97,-32768,   -90,    98,-32768,-32768,-32768,
  2269,-32768,-32768,    87,-32768,    92,-32768,  4644,-32768,-32768,
-32768,-32768,-32768,-32768,-32768,   100,   896,    99,-32768,-32768,
-32768,-32768,   102,   896,   103,-32768,-32768,   896,   104,-32768,
   896,   105,-32768,   896,   106,-32768,   896,  1224,-32768,-32768,
-32768,   107,-32768,  2269,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,  2269,  2269,   110,   113,   255,  2269,  2269,   114,  4230,
   115,  2269,   116,  2269,   117,  4455,   118,   119,   120,  4268,
  2269,   121,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,   123,  2269,  2269,  2269,  2269,  2269,   583,  5010,
  5010,  5010,-32768,-32768,   125,-32768,-32768,  2269,  2269,-32768,
  2269,  2269,   126,-32768,-32768,   127,-32768,-32768,  2269,  4789,
-32768,   128,  2269,  2269,  2269,   129,   130,  1249,-32768,  1378,
-32768,-32768,-32768,  2269,  2269,-32768,-32768,   132,-32768,   133,
-32768,-32768,-32768,-32768,   896,-32768,-32768,-32768,  5010,-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,   112,  1785,  1913,  1938,-32768,    63,-32768,  5010,-32768,
-32768,-32768,  1963,  2091,   135,-32768,   136,-32768,-32768,    56,
-32768,-32768,-32768,-32768,  3594,   149,   138,  4972,   292,  3594,
    67,  3594,  3594,  3594,  3594,  3691,  5010,   294,   297,   148,
   152,   153,   156,  5010,   313,   159,  3178,  4789,   158,   160,
   318,    85,-32768,   166,-32768,  2269,   167,-32768,  2269,   168,
-32768,  2269,   169,-32768,  2269,  5010,  5010,    35,   171,  5010,
  5010,  5010,  5010,  5010,    75,    85,  2116,-32768,-32768,-32768,
-32768,-32768,-32768,  2269,-32768,-32768,-32768,-32768,  5010,-32768,
   -90,-32768,   -90,   -90,-32768,   896,-32768,-32768,-32768,-32768,
-32768,   174,   176,-32768,   896,-32768,-32768,-32768,   896,-32768,
   896,-32768,   896,-32768,   896,-32768,   170,  2269,-32768,-32768,
   177,   325,-32768,  4417,-32768,  2269,-32768,   197,-32768,  4606,
-32768,   199,   200,-32768,  2269,   201,   202,-32768,-32768,   203,
-32768,-32768,   583,  5010,  5010,  5010,  2269,  2269,-32768,-32768,
  2269,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,   219,
  2269,-32768,-32768,-32768,-32768,-32768,-32768,    85,   173,   204,
   209,   357,   210,  3765,-32768,-32768,-32768,-32768,-32768,   205,
   206,-32768,-32768,-32768,-32768,-32768,-32768,-32768,  2269,   241,
-32768,-32768,-32768,    64,-32768,-32768,-32768,-32768,   241,-32768,
-32768,-32768,   401,-32768
};

static const short yypgoto[] = {-32768,
-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   207,-32768,   208,-32768,-32768,-32768,
-32768,-32768,-32768,-32768,   304,-32768,-32768,  -209,  -587,-32768,
-32768,-32768,  -306,-32768,  -405,-32768,    15,  -229,-32768,  -254,
  -148,  -163,-32768,  -236,  -252,  -234,  -196,-32768,-32768,  -264,
-32768,-32768,  -207,-32768,  -203,   178,-32768,  -249,-32768,  -250,
-32768,  -248,-32768,  -247,   -10,  -220,  -300,-32768,    22,  -211,
   175,  -168,-32768,-32768
};


#define	YYLAST		5417


static const short yytable[] = {    62,
    65,   428,   357,   443,    69,   466,   359,   468,    74,    75,
   442,   289,   486,   383,   673,   429,   432,   479,    32,   481,
    66,   528,    31,  -229,   131,   132,   133,   134,   135,   136,
   440,   362,    67,   405,   365,   441,   137,   138,   139,   140,
   141,   354,    70,    82,   143,   144,   145,   146,   147,   414,
   148,   494,   415,   292,    71,   456,   471,   489,   490,    72,
   472,   496,   195,   362,   467,   405,   365,   399,    83,   487,
   421,   372,   382,   387,   437,   367,   400,   401,   204,   208,
   209,   362,    84,   405,   365,   214,    86,   454,   454,   457,
   529,   453,   460,   284,   193,   465,   465,   454,   465,   406,
   379,   380,    87,   476,   477,   407,    88,   285,   202,   482,
   483,    76,   213,   362,   488,   405,   365,   218,   710,   711,
   286,   362,   290,   405,   365,   433,   379,   380,   434,   287,
   435,     4,     5,     6,     7,     8,     9,   288,   299,   300,
   301,   302,   303,   304,   305,   306,   307,   308,   309,   310,
   311,   312,   313,   314,   315,   316,   317,   318,   319,   320,
   321,   322,   323,   324,   325,   326,   327,   328,   329,   330,
   331,   332,   333,   334,   335,   336,   337,   338,   339,   340,
   291,   406,   607,   342,   525,   296,   527,   407,   648,    59,
   406,   379,   380,   198,   199,   672,   407,   674,   675,   353,
   200,   201,   347,   416,   491,   492,   379,   380,   361,   377,
   384,   388,   391,   394,   397,   398,   404,   348,   413,   355,
   417,   418,    82,   422,   424,   349,   431,   436,   516,   517,
   444,   445,   446,   447,   448,   381,   386,   390,   393,   396,
   600,   601,   408,   458,   459,   358,   461,   462,   708,   709,
   427,   292,   469,   473,   474,   475,   643,   647,   478,   360,
   480,    59,   579,   497,   484,   485,   210,   211,   500,   518,
   495,   608,   535,   501,   520,   522,   616,   536,   513,   514,
   515,   526,   532,    89,   540,   612,   539,   541,   542,   543,
   544,   545,   547,   550,    90,   548,   588,    91,   549,   551,
   553,   554,   555,   557,   558,   559,   561,   593,   562,   627,
   576,   577,   578,   580,   581,   582,   626,   585,   586,   597,
   598,   603,   604,   659,   649,   610,   613,   629,   662,   663,
   664,   665,   635,   617,   630,   631,   642,   646,   632,   523,
   633,   524,   634,   637,    92,    93,   638,   650,   651,    94,
   644,   653,   654,   655,   656,   678,   680,   147,   660,    95,
   689,   676,   679,   677,   666,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
   176,   177,   682,  -174,  -169,  -184,  -182,   696,   684,   701,
   702,   694,    96,    97,    98,    99,   695,   697,   652,   703,
   714,   217,   712,   685,   687,   344,   686,   688,   345,   147,
     0,     0,   423,     0,   465,   147,     0,     0,     0,   147,
     0,     0,   667,   100,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   205,     0,     0,     0,   566,   569,
   572,   575,   161,   162,   163,   164,   165,   166,   167,   168,
   169,   170,   171,   172,   173,   174,   175,   176,   177,   147,
     0,     0,     0,     0,   186,   187,   188,   189,   190,     0,
     0,   693,     0,     0,    33,    34,     0,     0,     0,     0,
    35,    36,    37,     0,    38,    39,    40,     0,   587,     0,
     0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
    46,     0,     0,     0,     0,   690,   691,     0,   594,    47,
    48,     0,     0,     0,   692,     0,     0,     0,     0,     0,
   698,     0,     0,     0,   606,     0,    49,    50,    51,   615,
     0,   619,   621,   623,   625,     0,   628,     0,     0,     0,
     0,     0,     0,   636,     0,   206,   207,   645,     0,   605,
     0,     0,     0,     0,   614,     0,   618,   620,   622,   624,
     0,     0,     0,     0,     0,   657,   658,     0,     0,   661,
     0,   641,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   563,     0,     0,   671,    54,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    55,    56,
     0,     0,     0,    57,    58,     0,     0,     0,    59,     0,
     0,    60,    61,   147,     0,    33,    34,     0,     0,   147,
     0,    35,    36,    37,     0,    38,    39,    40,     0,     0,
     0,     0,   566,   569,   572,   575,    41,    42,    43,    44,
    45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
    47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   699,     0,     0,     0,    49,    50,    51,
     0,     0,     0,     0,     0,   713,     2,     0,     0,   -65,
   -65,   -65,   -65,   -65,   -65,   -65,    52,    53,   -65,   -65,
   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
   -65,   -65,   -65,   -65,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     3,
   -65,   -65,   -65,   -65,     0,     0,     0,   -65,     0,     0,
    54,   -65,   -65,   -65,   -65,   -65,   -65,     0,     0,     4,
     5,     6,     7,     8,     9,     0,     0,     0,     0,    55,
    56,     0,     0,     0,    57,    58,     0,     0,     0,    59,
     0,     0,    60,    61,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    10,    11,    12,    13,    14,    15,    16,
    17,   -65,   -65,    18,     0,     0,   -65,     0,   -65,     0,
     0,    19,    20,    21,    22,    23,   -65,    24,   -65,   -65,
   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
     0,   -65,   -65,   -65,   -65,    25,     0,     0,   -65,   -65,
   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,   -65,
   -65,   -65,   -65,     0,     0,   -65,   -65,   -65,   -65,   -65,
    26,    27,    28,   149,   150,   151,   152,   153,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   -65,     0,     0,     0,     0,     0,     0,     0,   149,   150,
   151,   152,   153,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   149,   150,   151,   152,   153,     0,     0,
     0,     0,     0,     0,     0,   154,   155,   156,   157,   158,
   159,   160,     0,   161,   162,   163,   164,   165,   166,   167,
   168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
   154,   155,   156,   157,   158,   159,   160,     0,   161,   162,
   163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
   173,   174,   175,   176,   177,   154,   155,   156,   157,   158,
   159,   160,     0,   161,   162,   163,   164,   165,   166,   167,
   168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   178,     0,   179,   180,   181,   182,   183,
   184,   185,   186,   187,   188,   189,   190,   149,   150,   151,
   152,   153,     0,     0,     0,     0,     0,   298,   178,     0,
   179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
   189,   190,   149,   150,   151,   152,   153,     0,   297,     0,
     0,     0,     0,   178,     0,   179,   180,   181,   182,   183,
   184,   185,   186,   187,   188,   189,   190,   149,   150,   151,
   152,   153,  -262,     0,     0,     0,     0,     0,     0,   154,
   155,   156,   157,   158,   159,   160,     0,   161,   162,   163,
   164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
   174,   175,   176,   177,   154,   155,   156,   157,   158,   159,
   160,     0,   161,   162,   163,   164,   165,   166,   167,   168,
   169,   170,   171,   172,   173,   174,   175,   176,   177,   154,
   155,   156,   157,   158,   159,   160,     0,   161,   162,   163,
   164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
   174,   175,   176,   177,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
   177,     0,     0,     0,     0,     0,     0,   178,     0,   179,
   180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
   190,     0,     0,     0,   351,   352,   149,   150,   151,   152,
   153,     0,   178,     0,   179,   180,   181,   182,   183,   184,
   185,   186,   187,   188,   189,   190,     0,     0,     0,     0,
   194,   149,   150,   151,   152,   153,     0,   178,     0,   179,
   180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
   190,     0,     0,     0,     0,   350,   149,   150,   151,   152,
   153,     0,     0,     0,     0,   188,   189,   190,   154,   155,
   156,   157,   158,   159,   160,     0,   161,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
   175,   176,   177,   154,   155,   156,   157,   158,   159,   160,
     0,   161,   162,   163,   164,   165,   166,   167,   168,   169,
   170,   171,   172,   173,   174,   175,   176,   177,   154,   155,
   156,   157,   158,   159,   160,     0,   161,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
   175,   176,   177,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   178,     0,   179,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     0,     0,     0,     0,   499,   149,   150,   151,   152,   153,
     0,   178,     0,   179,   180,   181,   182,   183,   184,   185,
   186,   187,   188,   189,   190,     0,     0,     0,     0,   546,
   149,   150,   151,   152,   153,     0,   178,     0,   179,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     0,     0,     0,     0,   583,   149,   150,   151,   152,   153,
     0,     0,     0,     0,     0,     0,     0,   154,   155,   156,
   157,   158,   159,   160,     0,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
   176,   177,   154,   155,   156,   157,   158,   159,   160,     0,
   161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
   171,   172,   173,   174,   175,   176,   177,   154,   155,   156,
   157,   158,   159,   160,     0,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
   176,   177,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   178,     0,   179,   180,   181,
   182,   183,   184,   185,   186,   187,   188,   189,   190,     0,
     0,     0,     0,   584,   149,   150,   151,   152,   153,     0,
   178,     0,   179,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,     0,     0,     0,   191,     0,   149,
   150,   151,   152,   153,     0,   178,     0,   179,   180,   181,
   182,   183,   184,   185,   186,   187,   188,   189,   190,     0,
     0,     0,   192,     0,   149,   150,   151,   152,   153,     0,
     0,     0,     0,     0,     0,     0,   154,   155,   156,   157,
   158,   159,   160,     0,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
   177,   154,   155,   156,   157,   158,   159,   160,     0,   161,
   162,   163,   164,   165,   166,   167,   168,   169,   170,   171,
   172,   173,   174,   175,   176,   177,   154,   155,   156,   157,
   158,   159,   160,     0,   161,   162,   163,   164,   165,   166,
   167,   168,   169,   170,   171,   172,   173,   174,   175,   176,
   177,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   178,     0,   179,   180,   181,   182,
   183,   184,   185,   186,   187,   188,   189,   190,     0,     0,
     0,   196,   149,   150,   151,   152,   153,     0,     0,   178,
     0,   179,   180,   181,   182,   183,   184,   185,   186,   187,
   188,   189,   190,     0,     0,     0,   197,   149,   150,   151,
   152,   153,     0,     0,   178,     0,   179,   180,   181,   182,
   183,   184,   185,   186,   187,   188,   189,   190,     0,     0,
     0,   346,   149,   150,   151,   152,   153,     0,     0,     0,
     0,     0,     0,     0,   154,   155,   156,   157,   158,   159,
   160,     0,   161,   162,   163,   164,   165,   166,   167,   168,
   169,   170,   171,   172,   173,   174,   175,   176,   177,   154,
   155,   156,   157,   158,   159,   160,     0,   161,   162,   163,
   164,   165,   166,   167,   168,   169,   170,   171,   172,   173,
   174,   175,   176,   177,   154,   155,   156,   157,   158,   159,
   160,     0,   161,   162,   163,   164,   165,   166,   167,   168,
   169,   170,   171,   172,   173,   174,   175,   176,   177,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,   178,     0,   179,   180,   181,   182,   183,   184,
   185,   186,   187,   188,   189,   190,     0,     0,     0,   498,
   149,   150,   151,   152,   153,     0,     0,   178,     0,   179,
   180,   181,   182,   183,   184,   185,   186,   187,   188,   189,
   190,     0,     0,     0,   521,   149,   150,   151,   152,   153,
     0,     0,   178,     0,   179,   180,   181,   182,   183,   184,
   185,   186,   187,   188,   189,   190,     0,     0,     0,   589,
   149,   150,   151,   152,   153,     0,     0,     0,     0,     0,
     0,     0,   154,   155,   156,   157,   158,   159,   160,     0,
   161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
   171,   172,   173,   174,   175,   176,   177,   154,   155,   156,
   157,   158,   159,   160,     0,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
   176,   177,   154,   155,   156,   157,   158,   159,   160,     0,
   161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
   171,   172,   173,   174,   175,   176,   177,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   178,     0,   179,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,     0,     0,     0,   590,   149,   150,
   151,   152,   153,     0,     0,   178,     0,   179,   180,   181,
   182,   183,   184,   185,   186,   187,   188,   189,   190,     0,
     0,     0,   591,   149,   150,   151,   152,   153,     0,     0,
   178,     0,   179,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,     0,     0,     0,   595,   149,   150,
   151,   152,   153,     0,     0,     0,     0,     0,     0,     0,
   154,   155,   156,   157,   158,   159,   160,     0,   161,   162,
   163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
   173,   174,   175,   176,   177,   154,   155,   156,   157,   158,
   159,   160,     0,   161,   162,   163,   164,   165,   166,   167,
   168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
   154,   155,   156,   157,   158,   159,   160,     0,   161,   162,
   163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
   173,   174,   175,   176,   177,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   178,     0,
   179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
   189,   190,     0,     0,     0,   596,   149,   150,   151,   152,
   153,     0,     0,   178,     0,   179,   180,   181,   182,   183,
   184,   185,   186,   187,   188,   189,   190,     0,     0,     0,
   668,   149,   150,   151,   152,     0,     0,     0,   178,   519,
   179,   180,   181,   182,   183,   184,   185,   186,   187,   188,
   189,   190,     0,     0,     0,     0,   149,   150,   151,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   154,   155,
   156,   157,   158,   159,   160,     0,   161,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
   175,   176,   177,   154,   155,   156,   157,   158,   159,   160,
     0,   161,   162,   163,   164,   165,   166,   167,   168,   169,
   170,   171,   172,   173,   174,   175,   176,   177,   154,   155,
   156,   157,   158,   159,   160,     0,   161,   162,   163,   164,
   165,   166,   167,   168,   169,   170,   171,   172,   173,   174,
   175,   176,   177,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   178,     0,   179,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
   149,     0,   151,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   179,   180,   181,   182,   183,   184,   185,
   186,   187,   188,   189,   190,   149,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   179,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
   102,   103,   154,   155,   156,   157,   158,   159,   160,     0,
   161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
   171,   172,   173,   174,   175,   176,   177,   154,   155,   156,
   157,   158,   159,   160,     0,   161,   162,   163,   164,   165,
   166,   167,   168,   169,   170,   171,   172,   173,   174,   175,
   176,   177,   104,     0,     0,     0,     0,     0,     0,   105,
   106,     0,     0,     0,     0,     0,     0,   107,   108,   109,
   110,   111,   112,   113,   114,     0,     0,     0,     0,     0,
     0,   115,   116,   117,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   118,     0,
     0,     0,     0,   180,   181,   182,   183,   184,   185,   186,
   187,   188,   189,   190,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   181,
   182,   183,   184,   185,   186,   187,   188,   189,   190,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,   119,   120,
   121,   122,     0,     0,     0,     0,   123,   124,   125,   126,
   127,   502,     0,   503,   504,   505,   506,   507,   508,     0,
     0,   509,     0,   510,     0,    33,    34,     0,     0,     0,
     0,    35,    36,    37,     0,    38,    39,    40,     0,     0,
     0,     0,     0,     0,     0,     0,    41,    42,    43,    44,
    45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
    47,    48,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   362,
   363,   405,   365,   406,   379,   380,    52,    53,     0,   407,
   425,     0,     0,    33,    34,     0,     0,     0,     0,    35,
    36,    37,     0,    38,    39,    40,     0,   511,     0,     0,
     0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
     0,     0,     0,     0,     0,     0,     0,     0,    47,    48,
    54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    49,    50,    51,     0,    55,
    56,     0,     0,     0,    57,    58,     0,     0,     0,    59,
     0,     0,    60,    61,    52,    53,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   362,   363,   405,   365,
   406,   379,   380,     0,     0,     0,   407,     0,     0,     0,
    33,    34,     0,     0,     0,     0,    35,    36,    37,     0,
    38,    39,    40,     0,     0,     0,     0,     0,    54,     0,
     0,    41,    42,    43,    44,    45,    46,     0,     0,     0,
     0,     0,     0,     0,     0,    47,    48,    55,    56,     0,
     0,     0,    57,    58,     0,     0,     0,   426,     0,     0,
    60,    61,    49,    50,    51,     0,     0,     0,     0,     0,
     0,     0,     0,     0,   362,   363,   378,   365,     0,   379,
   380,    52,    53,     0,     0,     0,   367,     0,    33,    34,
     0,     0,     0,     0,    35,    36,    37,     0,    38,    39,
    40,     0,     0,     0,     0,     0,     0,     0,     0,    41,
    42,    43,    44,    45,    46,     0,     0,     0,     0,     0,
     0,     0,     0,    47,    48,    54,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    49,    50,    51,     0,    55,    56,     0,     0,     0,    57,
    58,     0,     0,     0,   368,     0,     0,    60,    61,    52,
    53,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   362,   363,   364,   365,     0,   366,     0,     0,     0,
     0,     0,     0,   367,     0,    33,    34,     0,     0,     0,
     0,    35,    36,    37,     0,    38,    39,    40,     0,     0,
     0,     0,     0,    54,     0,     0,    41,    42,    43,    44,
    45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
    47,    48,    55,    56,     0,     0,     0,    57,    58,     0,
     0,     0,   368,     0,     0,    60,    61,    49,    50,    51,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   362,
   363,   385,   365,     0,     0,     0,    52,    53,     0,     0,
     0,   367,     0,    33,    34,     0,     0,     0,     0,    35,
    36,    37,     0,    38,    39,    40,     0,     0,     0,     0,
     0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
     0,     0,     0,     0,     0,     0,     0,     0,    47,    48,
    54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    49,    50,    51,     0,    55,
    56,     0,     0,     0,    57,    58,     0,     0,     0,   368,
     0,     0,    60,    61,    52,    53,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   362,   363,   405,   365,
     0,     0,     0,     0,     0,     0,     0,   639,     0,     0,
    33,    34,     0,     0,     0,     0,    35,    36,    37,     0,
    38,    39,    40,     0,     0,     0,     0,     0,    54,     0,
     0,    41,    42,    43,    44,    45,    46,     0,     0,     0,
     0,     0,     0,     0,     0,    47,    48,    55,    56,     0,
     0,     0,    57,    58,     0,     0,     0,   368,     0,     0,
    60,    61,    49,    50,    51,     0,     0,     0,     0,     0,
   362,   363,   389,   365,     0,     0,     0,     0,     0,     0,
     0,    52,    53,     0,    33,    34,     0,     0,     0,     0,
    35,    36,    37,     0,    38,    39,    40,     0,     0,     0,
     0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
    46,     0,     0,     0,     0,     0,     0,     0,     0,    47,
    48,     0,     0,     0,     0,    54,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    49,    50,    51,     0,
     0,     0,     0,     0,    55,    56,     0,     0,     0,    57,
    58,     0,     0,     0,   640,    52,    53,    60,    61,     0,
     0,     0,     0,     0,     0,     0,     0,   362,   363,   392,
   365,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    33,    34,     0,     0,     0,     0,    35,    36,    37,
     0,    38,    39,    40,     0,     0,     0,     0,     0,    54,
     0,     0,    41,    42,    43,    44,    45,    46,     0,     0,
     0,     0,     0,     0,     0,     0,    47,    48,    55,    56,
     0,     0,     0,    57,    58,     0,     0,     0,   368,     0,
     0,    60,    61,    49,    50,    51,     0,     0,     0,     0,
     0,   362,   363,   395,   365,     0,     0,     0,     0,     0,
     0,     0,    52,    53,     0,    33,    34,     0,     0,     0,
     0,    35,    36,    37,     0,    38,    39,    40,     0,     0,
     0,     0,     0,     0,     0,     0,    41,    42,    43,    44,
    45,    46,     0,     0,     0,     0,     0,     0,     0,     0,
    47,    48,     0,     0,     0,     0,    54,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    49,    50,    51,
     0,     0,     0,     0,     0,    55,    56,     0,     0,     0,
    57,    58,     0,     0,     0,   368,    52,    53,    60,    61,
     0,     0,     0,     0,     0,     0,     0,     0,   362,     0,
   405,   365,     0,     0,     0,     0,   419,     0,     0,     0,
     0,     0,    33,    34,     0,     0,     0,     0,    35,    36,
    37,     0,    38,    39,    40,     0,     0,     0,     0,     0,
    54,     0,     0,    41,    42,    43,    44,    45,    46,     0,
     0,     0,     0,     0,     0,     0,     0,    47,    48,    55,
    56,     0,     0,     0,    57,    58,     0,     0,     0,   368,
     0,     0,    60,    61,    49,    50,    51,     0,     0,     0,
     0,     0,   362,   363,   405,   365,     0,     0,     0,     0,
     0,     0,     0,    52,    53,     0,    33,    34,     0,     0,
     0,     0,    35,    36,    37,     0,    38,    39,    40,     0,
     0,     0,     0,     0,     0,     0,     0,    41,    42,    43,
    44,    45,    46,     0,     0,     0,     0,     0,     0,     0,
     0,    47,    48,     0,     0,     0,     0,    54,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
    51,     0,     0,     0,     0,     0,    55,    56,     0,     0,
     0,    57,    58,     0,     0,     0,   420,    52,    53,    60,
    61,     0,     0,     0,     0,     0,     0,     0,     0,   362,
     0,   405,   365,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    33,    34,     0,     0,     0,     0,    35,
    36,    37,     0,    38,    39,    40,     0,     0,     0,     0,
     0,    54,     0,     0,    41,    42,    43,    44,    45,    46,
     0,     0,     0,     0,     0,     0,     0,     0,    47,    48,
    55,    56,     0,     0,     0,    57,    58,     0,     0,     0,
   368,     0,     0,    60,    61,    49,    50,    51,     0,     0,
     0,     0,     0,   362,     0,   405,   365,     0,     0,     0,
     0,     0,     0,     0,    52,    53,     0,    33,    34,     0,
     0,     0,     0,    35,    36,    37,     0,    38,    39,    40,
     0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
    43,    44,    45,    46,     0,     0,     0,     0,     0,     0,
     0,     0,    47,    48,     0,     0,     0,     0,    54,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
    50,    51,     0,     0,     0,     0,     0,    55,    56,     0,
     0,     0,    57,    58,     0,     0,     0,   368,    52,    53,
    60,    61,   219,   220,   221,   222,   223,   224,   225,     0,
     0,   226,   227,   228,   229,   230,   231,   232,   233,   234,
   235,   236,   237,   238,   239,   240,   241,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    54,     0,   242,   243,   244,     0,     0,     0,
   245,     0,     0,     0,     0,   246,   247,     0,   248,   249,
     0,    55,    56,     0,     0,     0,    57,    58,     0,     0,
     0,    59,   154,   155,    60,    61,     0,     0,     0,     0,
   161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
   171,   172,   173,   174,   175,   176,   177,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   250,     0,     0,     0,     0,     0,     0,     0,     0,
     0,   251,   252,   253,   254,   255,   256,   257,   258,   259,
   260,   261,   262,     0,   263,   264,   265,   266,     0,     0,
     0,   267,   268,   269,   270,   271,   272,   273,   274,   275,
   276,   277,     0,     0,   399,     0,   379,   380,   278,   279,
   280,   281,   282,   400,   401,    33,    34,     0,     0,     0,
     0,    35,    36,    37,     0,    38,    39,    40,     0,   186,
   187,   188,   189,   190,     0,     0,    41,    42,    43,    44,
    45,    46,     0,   399,     0,     0,     0,     0,     0,     0,
    47,    48,   400,   401,    33,    34,     0,     0,     0,     0,
    35,    36,    37,     0,    38,    39,    40,    49,    50,    51,
     0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
    46,     0,   399,     0,     0,     0,    52,    53,     0,    47,
    48,     0,   401,    33,    34,     0,     0,     0,     0,    35,
    36,    37,     0,    38,    39,    40,    49,    50,    51,     0,
     0,     0,     0,     0,    41,    42,    43,    44,    45,    46,
     0,     0,     0,     0,     0,    52,    53,     0,    47,    48,
    54,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    49,    50,    51,     0,    55,
    56,     0,     0,     0,    57,    58,     0,     0,     0,   470,
     0,     0,    60,    61,    52,    53,     0,     0,     0,    54,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    55,    56,
     0,     0,     0,    57,    58,     0,     0,     0,    59,     0,
     0,    60,    61,     0,     0,     0,     0,     0,    54,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    55,    56,     0,
     0,   552,    57,    58,     0,     0,     0,    59,     0,     0,
    60,    61,    33,    34,     0,     0,     0,     0,    35,    36,
    37,     0,    38,    39,    40,     0,     0,     0,     0,     0,
     0,     0,     0,    41,    42,    43,    44,    45,    46,   560,
     0,     0,     0,     0,     0,     0,     0,    47,    48,     0,
    33,    34,     0,     0,     0,     0,    35,    36,    37,     0,
    38,    39,    40,     0,    49,    50,    51,     0,     0,     0,
     0,    41,    42,    43,    44,    45,    46,     0,     0,     0,
     0,     0,     0,    52,    53,    47,    48,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    49,    50,    51,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    52,    53,     0,     0,     0,     0,    54,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    55,    56,     0,     0,
     0,    57,    58,     0,     0,     0,    59,     0,     0,    60,
    61,     0,     0,     0,     0,    54,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    55,    56,     0,     0,   681,    57,
    58,     0,     0,     0,    59,     0,     0,    60,    61,    33,
    34,     0,     0,     0,     0,    35,    36,    37,     0,    38,
    39,    40,     0,     0,     0,     0,     0,     0,     0,     0,
    41,    42,    43,    44,    45,    46,     0,   556,   537,   538,
     0,     0,     0,     0,    47,    48,     0,    33,    34,     0,
     0,     0,     0,    35,    36,    37,     0,    38,    39,    40,
     0,    49,    50,    51,     0,     0,     0,     0,    41,    42,
    43,    44,    45,    46,     0,     0,     0,     0,     0,     0,
    52,    53,    47,    48,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
    50,    51,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    52,    53,
     0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    55,    56,     0,     0,     0,    57,    58,
     0,     0,     0,    59,     0,     0,    60,    61,     0,     0,
     0,     0,    54,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    55,    56,     0,     0,     0,    57,    58,   683,   537,
   538,    59,     0,     0,    60,    61,     0,     0,    33,    34,
     0,     0,     0,     0,    35,    36,    37,     0,    38,    39,
    40,     0,     0,     0,     0,     0,     0,     0,     0,    41,
    42,    43,    44,    45,    46,     0,     0,   537,   538,     0,
     0,     0,     0,    47,    48,     0,    33,    34,     0,     0,
     0,     0,    35,    36,    37,     0,    38,    39,    40,     0,
    49,    50,    51,     0,     0,     0,     0,    41,    42,    43,
    44,    45,    46,     0,     0,     0,     0,     0,     0,    52,
    53,    47,    48,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    49,    50,
    51,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,    52,    53,     0,
     0,     0,     0,    54,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    55,    56,     0,     0,     0,    57,    58,     0,
     0,     0,    59,     0,     0,    60,    61,     0,     0,     0,
     0,    54,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    55,    56,   379,   380,     0,    57,    58,     0,     0,     0,
    59,    33,    34,    60,    61,     0,     0,    35,    36,    37,
     0,    38,    39,    40,     0,     0,     0,     0,     0,     0,
     0,     0,    41,    42,    43,    44,    45,    46,     0,     0,
     0,     0,     0,     0,     0,     0,    47,    48,     0,    33,
    34,     0,     0,     0,     0,    35,    36,    37,     0,    38,
    39,    40,     0,    49,    50,    51,     0,     0,     0,     0,
    41,    42,    43,    44,    45,    46,     0,     0,     0,     0,
     0,     0,    52,    53,    47,    48,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,    49,    50,    51,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    52,    53,     0,     0,     0,     0,    54,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,    55,    56,     0,     0,     0,
    57,    58,     0,     0,     0,    59,     0,     0,    60,    61,
     0,     0,     0,     0,    54,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    55,    56,     0,     0,     0,    57,    58,
     0,   203,     0,    59,    33,    34,    60,    61,     0,     0,
    35,    36,    37,     0,    38,    39,    40,     0,     0,     0,
     0,     0,     0,     0,     0,    41,    42,    43,    44,    45,
    46,     0,     0,     0,     0,     0,     0,     0,     0,    47,
    48,     0,    33,    34,     0,     0,     0,     0,    35,    36,
    37,     0,    38,    39,    40,     0,    49,    50,    51,     0,
     0,     0,     0,    41,    42,    43,    44,    45,    46,     0,
     0,     0,     0,     0,     0,    52,    53,    47,    48,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,    49,    50,    51,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,    52,    53,     0,     0,     0,     0,    54,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    55,    56,
     0,     0,     0,    57,    58,     0,     0,     0,    59,   611,
     0,    60,    61,     0,     0,     0,     0,    54,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,    55,    56,     0,     0,
     0,    57,    58,     0,     0,     0,    59,    33,    34,    60,
    61,     0,     0,    35,    36,    37,     0,    38,    39,    40,
     0,     0,     0,     0,     0,     0,     0,     0,    41,    42,
    43,    44,    45,    46,     0,     0,     0,     0,     0,     0,
     0,     0,    47,    48,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    49,
    50,    51,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,    52,    53,
   154,   155,   156,   157,   158,   159,   160,     0,   161,   162,
   163,   164,   165,   166,   167,   168,   169,   170,   171,   172,
   173,   174,   175,   176,   177,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,   154,   155,   156,     0,   158,
   159,     0,    54,   161,   162,   163,   164,   165,   166,   167,
   168,   169,   170,   171,   172,   173,   174,   175,   176,   177,
     0,    55,    56,     0,     0,     0,    57,    58,     0,     0,
     0,   430,     0,     0,    60,    61,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   182,   183,   184,   185,   186,   187,   188,
   189,   190,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   183,
   184,   185,   186,   187,   188,   189,   190
};

static const short yycheck[] = {    10,
    11,   236,   214,   240,    15,   260,   216,   262,    19,    20,
   240,    62,   277,   221,   602,   236,   237,   270,   110,   272,
   185,   112,     1,   159,    35,    36,    37,    38,    39,    40,
   238,    29,   185,    31,    32,   239,    47,    48,    49,    50,
    51,   210,   185,    22,    55,    56,    57,    58,    59,    33,
    61,   281,    36,   189,   185,   252,   264,   278,   279,   185,
   264,   282,    73,    29,   261,    31,    32,    32,   185,   277,
   234,   220,   221,   222,   238,    41,    41,    42,    89,    90,
    91,    29,   185,    31,    32,    96,   185,   251,   252,   253,
   181,    39,   256,   104,   112,   259,   260,   261,   262,    33,
    34,    35,   185,   267,   268,    39,   185,   118,   141,   273,
   274,    44,   185,    29,   278,    31,    32,   185,   706,   707,
   169,    29,   173,    31,    32,    33,    34,    35,    36,   177,
    38,    64,    65,    66,    67,    68,    69,   178,   149,   150,
   151,   152,   153,   154,   155,   156,   157,   158,   159,   160,
   161,   162,   163,   164,   165,   166,   167,   168,   169,   170,
   171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
   181,   182,   183,   184,   185,   186,   187,   188,   189,   190,
   173,    33,    34,   194,   353,   141,   355,    39,    31,   187,
    33,    34,    35,   185,   186,   601,    39,   603,   604,   112,
   185,   186,   185,   187,    33,    34,    34,    35,   219,   220,
   221,   222,   223,   224,   225,   226,   227,   185,   229,   112,
   231,   232,   201,   234,   235,   185,   237,   135,   185,   186,
   241,   242,   243,   244,   245,   221,   222,   223,   224,   225,
   185,   186,   228,   254,   255,   186,   257,   258,   185,   186,
   236,   189,   263,   264,   265,   266,   557,   558,   269,   186,
   271,   187,   470,   185,   275,   276,    92,    93,   185,   159,
   281,   536,   186,   185,   185,   185,   541,   186,   289,   290,
   291,   185,   185,    45,   186,   538,   187,   186,   186,   186,
   186,   186,   186,    39,    56,   186,   185,    59,   186,   186,
   186,   186,   186,   186,   186,   186,   186,   517,   186,   546,
   186,   186,   186,   186,   186,   186,   546,   186,   186,   185,
   185,   533,   534,   578,   559,   188,    35,    34,   581,   582,
   583,   584,   553,   541,    38,   188,   557,   558,   187,   350,
   188,   352,   187,    31,   106,   107,   188,   188,    31,   111,
   558,   186,   186,   186,   186,   186,    32,   368,   188,   121,
   142,   188,   186,   188,   585,    78,    79,    80,    81,    82,
    83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
    93,    94,   186,   185,   185,   185,   185,    31,   186,   185,
   185,   188,   154,   155,   156,   157,   188,   188,   562,   159,
     0,    98,   709,   653,   655,   199,   654,   656,   201,   420,
    -1,    -1,   235,    -1,   578,   426,    -1,    -1,    -1,   430,
    -1,    -1,   586,   185,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,     3,    -1,    -1,    -1,   449,   450,
   451,   452,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,   470,
    -1,    -1,    -1,    -1,   177,   178,   179,   180,   181,    -1,
    -1,   679,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,
    49,    50,    51,    -1,    53,    54,    55,    -1,   499,    -1,
    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
    69,    -1,    -1,    -1,    -1,   674,   675,    -1,   519,    78,
    79,    -1,    -1,    -1,   678,    -1,    -1,    -1,    -1,    -1,
   684,    -1,    -1,    -1,   535,    -1,    95,    96,    97,   540,
    -1,   542,   543,   544,   545,    -1,   547,    -1,    -1,    -1,
    -1,    -1,    -1,   554,    -1,   114,   115,   558,    -1,   535,
    -1,    -1,    -1,    -1,   540,    -1,   542,   543,   544,   545,
    -1,    -1,    -1,    -1,    -1,   576,   577,    -1,    -1,   580,
    -1,   557,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,     3,    -1,    -1,   599,   158,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,
    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,    -1,
    -1,   190,   191,   634,    -1,    43,    44,    -1,    -1,   640,
    -1,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
    -1,    -1,   653,   654,   655,   656,    64,    65,    66,    67,
    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   684,    -1,    -1,    -1,    95,    96,    97,
    -1,    -1,    -1,    -1,    -1,     0,     1,    -1,    -1,     4,
     5,     6,     7,     8,     9,    10,   114,   115,    13,    14,
    15,    16,    17,    18,    19,    20,    21,    22,    23,    24,
    25,    26,    27,    28,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    44,
    45,    46,    47,    48,    -1,    -1,    -1,    52,    -1,    -1,
   158,    56,    57,    58,    59,    60,    61,    -1,    -1,    64,
    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,   177,
   178,    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,
    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    98,    99,   100,   101,   102,   103,   104,
   105,   106,   107,   108,    -1,    -1,   111,    -1,   113,    -1,
    -1,   116,   117,   118,   119,   120,   121,   122,   123,   124,
   125,   126,   127,   128,   129,   130,   131,   132,   133,   134,
    -1,   136,   137,   138,   139,   140,    -1,    -1,   143,   144,
   145,   146,   147,   148,   149,   150,   151,   152,   153,   154,
   155,   156,   157,    -1,    -1,   160,   161,   162,   163,   164,
   165,   166,   167,     8,     9,    10,    11,    12,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   185,    -1,    -1,    -1,    -1,    -1,    -1,    -1,     8,     9,
    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,     8,     9,    10,    11,    12,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,
    75,    76,    -1,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
    70,    71,    72,    73,    74,    75,    76,    -1,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
    90,    91,    92,    93,    94,    70,    71,    72,    73,    74,
    75,    76,    -1,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   168,    -1,   170,   171,   172,   173,   174,
   175,   176,   177,   178,   179,   180,   181,     8,     9,    10,
    11,    12,    -1,    -1,    -1,    -1,    -1,   192,   168,    -1,
   170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
   180,   181,     8,     9,    10,    11,    12,    -1,   188,    -1,
    -1,    -1,    -1,   168,    -1,   170,   171,   172,   173,   174,
   175,   176,   177,   178,   179,   180,   181,     8,     9,    10,
    11,    12,   187,    -1,    -1,    -1,    -1,    -1,    -1,    70,
    71,    72,    73,    74,    75,    76,    -1,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    70,    71,    72,    73,    74,    75,
    76,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    70,
    71,    72,    73,    74,    75,    76,    -1,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    78,    79,    80,    81,    82,    83,
    84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
    94,    -1,    -1,    -1,    -1,    -1,    -1,   168,    -1,   170,
   171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
   181,    -1,    -1,    -1,   185,   186,     8,     9,    10,    11,
    12,    -1,   168,    -1,   170,   171,   172,   173,   174,   175,
   176,   177,   178,   179,   180,   181,    -1,    -1,    -1,    -1,
   186,     8,     9,    10,    11,    12,    -1,   168,    -1,   170,
   171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
   181,    -1,    -1,    -1,    -1,   186,     8,     9,    10,    11,
    12,    -1,    -1,    -1,    -1,   179,   180,   181,    70,    71,
    72,    73,    74,    75,    76,    -1,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
    92,    93,    94,    70,    71,    72,    73,    74,    75,    76,
    -1,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    70,    71,
    72,    73,    74,    75,    76,    -1,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   168,    -1,   170,   171,
   172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
    -1,    -1,    -1,    -1,   186,     8,     9,    10,    11,    12,
    -1,   168,    -1,   170,   171,   172,   173,   174,   175,   176,
   177,   178,   179,   180,   181,    -1,    -1,    -1,    -1,   186,
     8,     9,    10,    11,    12,    -1,   168,    -1,   170,   171,
   172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
    -1,    -1,    -1,    -1,   186,     8,     9,    10,    11,    12,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,
    73,    74,    75,    76,    -1,    78,    79,    80,    81,    82,
    83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
    93,    94,    70,    71,    72,    73,    74,    75,    76,    -1,
    78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    94,    70,    71,    72,
    73,    74,    75,    76,    -1,    78,    79,    80,    81,    82,
    83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   168,    -1,   170,   171,   172,
   173,   174,   175,   176,   177,   178,   179,   180,   181,    -1,
    -1,    -1,    -1,   186,     8,     9,    10,    11,    12,    -1,
   168,    -1,   170,   171,   172,   173,   174,   175,   176,   177,
   178,   179,   180,   181,    -1,    -1,    -1,   185,    -1,     8,
     9,    10,    11,    12,    -1,   168,    -1,   170,   171,   172,
   173,   174,   175,   176,   177,   178,   179,   180,   181,    -1,
    -1,    -1,   185,    -1,     8,     9,    10,    11,    12,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    73,
    74,    75,    76,    -1,    78,    79,    80,    81,    82,    83,
    84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
    94,    70,    71,    72,    73,    74,    75,    76,    -1,    78,
    79,    80,    81,    82,    83,    84,    85,    86,    87,    88,
    89,    90,    91,    92,    93,    94,    70,    71,    72,    73,
    74,    75,    76,    -1,    78,    79,    80,    81,    82,    83,
    84,    85,    86,    87,    88,    89,    90,    91,    92,    93,
    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   168,    -1,   170,   171,   172,   173,
   174,   175,   176,   177,   178,   179,   180,   181,    -1,    -1,
    -1,   185,     8,     9,    10,    11,    12,    -1,    -1,   168,
    -1,   170,   171,   172,   173,   174,   175,   176,   177,   178,
   179,   180,   181,    -1,    -1,    -1,   185,     8,     9,    10,
    11,    12,    -1,    -1,   168,    -1,   170,   171,   172,   173,
   174,   175,   176,   177,   178,   179,   180,   181,    -1,    -1,
    -1,   185,     8,     9,    10,    11,    12,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    70,    71,    72,    73,    74,    75,
    76,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    70,
    71,    72,    73,    74,    75,    76,    -1,    78,    79,    80,
    81,    82,    83,    84,    85,    86,    87,    88,    89,    90,
    91,    92,    93,    94,    70,    71,    72,    73,    74,    75,
    76,    -1,    78,    79,    80,    81,    82,    83,    84,    85,
    86,    87,    88,    89,    90,    91,    92,    93,    94,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   168,    -1,   170,   171,   172,   173,   174,   175,
   176,   177,   178,   179,   180,   181,    -1,    -1,    -1,   185,
     8,     9,    10,    11,    12,    -1,    -1,   168,    -1,   170,
   171,   172,   173,   174,   175,   176,   177,   178,   179,   180,
   181,    -1,    -1,    -1,   185,     8,     9,    10,    11,    12,
    -1,    -1,   168,    -1,   170,   171,   172,   173,   174,   175,
   176,   177,   178,   179,   180,   181,    -1,    -1,    -1,   185,
     8,     9,    10,    11,    12,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    70,    71,    72,    73,    74,    75,    76,    -1,
    78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    94,    70,    71,    72,
    73,    74,    75,    76,    -1,    78,    79,    80,    81,    82,
    83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
    93,    94,    70,    71,    72,    73,    74,    75,    76,    -1,
    78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   168,    -1,   170,   171,   172,   173,   174,   175,   176,   177,
   178,   179,   180,   181,    -1,    -1,    -1,   185,     8,     9,
    10,    11,    12,    -1,    -1,   168,    -1,   170,   171,   172,
   173,   174,   175,   176,   177,   178,   179,   180,   181,    -1,
    -1,    -1,   185,     8,     9,    10,    11,    12,    -1,    -1,
   168,    -1,   170,   171,   172,   173,   174,   175,   176,   177,
   178,   179,   180,   181,    -1,    -1,    -1,   185,     8,     9,
    10,    11,    12,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    70,    71,    72,    73,    74,    75,    76,    -1,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
    90,    91,    92,    93,    94,    70,    71,    72,    73,    74,
    75,    76,    -1,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
    70,    71,    72,    73,    74,    75,    76,    -1,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
    90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   168,    -1,
   170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
   180,   181,    -1,    -1,    -1,   185,     8,     9,    10,    11,
    12,    -1,    -1,   168,    -1,   170,   171,   172,   173,   174,
   175,   176,   177,   178,   179,   180,   181,    -1,    -1,    -1,
   185,     8,     9,    10,    11,    -1,    -1,    -1,   168,   169,
   170,   171,   172,   173,   174,   175,   176,   177,   178,   179,
   180,   181,    -1,    -1,    -1,    -1,     8,     9,    10,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    70,    71,
    72,    73,    74,    75,    76,    -1,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
    92,    93,    94,    70,    71,    72,    73,    74,    75,    76,
    -1,    78,    79,    80,    81,    82,    83,    84,    85,    86,
    87,    88,    89,    90,    91,    92,    93,    94,    70,    71,
    72,    73,    74,    75,    76,    -1,    78,    79,    80,    81,
    82,    83,    84,    85,    86,    87,    88,    89,    90,    91,
    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   168,    -1,   170,   171,
   172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
     8,    -1,    10,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   170,   171,   172,   173,   174,   175,   176,
   177,   178,   179,   180,   181,     8,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   170,   171,
   172,   173,   174,   175,   176,   177,   178,   179,   180,   181,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    11,    12,    70,    71,    72,    73,    74,    75,    76,    -1,
    78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    94,    70,    71,    72,
    73,    74,    75,    76,    -1,    78,    79,    80,    81,    82,
    83,    84,    85,    86,    87,    88,    89,    90,    91,    92,
    93,    94,    63,    -1,    -1,    -1,    -1,    -1,    -1,    70,
    71,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    80,
    81,    82,    83,    84,    85,    -1,    -1,    -1,    -1,    -1,
    -1,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   109,    -1,
    -1,    -1,    -1,   171,   172,   173,   174,   175,   176,   177,
   178,   179,   180,   181,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   172,
   173,   174,   175,   176,   177,   178,   179,   180,   181,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   169,   170,
   171,   172,    -1,    -1,    -1,    -1,   177,   178,   179,   180,
   181,    29,    -1,    31,    32,    33,    34,    35,    36,    -1,
    -1,    39,    -1,    41,    -1,    43,    44,    -1,    -1,    -1,
    -1,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
    30,    31,    32,    33,    34,    35,   114,   115,    -1,    39,
    40,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    49,
    50,    51,    -1,    53,    54,    55,    -1,   135,    -1,    -1,
    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    69,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    95,    96,    97,    -1,   177,
   178,    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,
    -1,    -1,   190,   191,   114,   115,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
    33,    34,    35,    -1,    -1,    -1,    39,    -1,    -1,    -1,
    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
    53,    54,    55,    -1,    -1,    -1,    -1,    -1,   158,    -1,
    -1,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    78,    79,   177,   178,    -1,
    -1,    -1,   182,   183,    -1,    -1,    -1,   187,    -1,    -1,
   190,   191,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    29,    30,    31,    32,    -1,    34,
    35,   114,   115,    -1,    -1,    -1,    41,    -1,    43,    44,
    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    53,    54,
    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    78,    79,   158,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    95,    96,    97,    -1,   177,   178,    -1,    -1,    -1,   182,
   183,    -1,    -1,    -1,   187,    -1,    -1,   190,   191,   114,
   115,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    29,    30,    31,    32,    -1,    34,    -1,    -1,    -1,
    -1,    -1,    -1,    41,    -1,    43,    44,    -1,    -1,    -1,
    -1,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
    -1,    -1,    -1,   158,    -1,    -1,    64,    65,    66,    67,
    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    78,    79,   177,   178,    -1,    -1,    -1,   182,   183,    -1,
    -1,    -1,   187,    -1,    -1,   190,   191,    95,    96,    97,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
    30,    31,    32,    -1,    -1,    -1,   114,   115,    -1,    -1,
    -1,    41,    -1,    43,    44,    -1,    -1,    -1,    -1,    49,
    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    69,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    95,    96,    97,    -1,   177,
   178,    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,
    -1,    -1,   190,   191,   114,   115,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,    32,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    40,    -1,    -1,
    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
    53,    54,    55,    -1,    -1,    -1,    -1,    -1,   158,    -1,
    -1,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    78,    79,   177,   178,    -1,
    -1,    -1,   182,   183,    -1,    -1,    -1,   187,    -1,    -1,
   190,   191,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,
    29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   114,   115,    -1,    43,    44,    -1,    -1,    -1,    -1,
    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
    79,    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,    -1,
    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,    -1,   182,
   183,    -1,    -1,    -1,   187,   114,   115,   190,   191,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    30,    31,
    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,
    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,   158,
    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,   177,   178,
    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,    -1,
    -1,   190,   191,    95,    96,    97,    -1,    -1,    -1,    -1,
    -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   114,   115,    -1,    43,    44,    -1,    -1,    -1,
    -1,    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,
    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    78,    79,    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,    97,
    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,    -1,
   182,   183,    -1,    -1,    -1,   187,   114,   115,   190,   191,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,    -1,
    31,    32,    -1,    -1,    -1,    -1,    37,    -1,    -1,    -1,
    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
   158,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,   177,
   178,    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,
    -1,    -1,   190,   191,    95,    96,    97,    -1,    -1,    -1,
    -1,    -1,    29,    30,    31,    32,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   114,   115,    -1,    43,    44,    -1,    -1,
    -1,    -1,    49,    50,    51,    -1,    53,    54,    55,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,    66,
    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    78,    79,    -1,    -1,    -1,    -1,   158,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,
    97,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,
    -1,   182,   183,    -1,    -1,    -1,   187,   114,   115,   190,
   191,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    29,
    -1,    31,    32,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    43,    44,    -1,    -1,    -1,    -1,    49,
    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,
    -1,   158,    -1,    -1,    64,    65,    66,    67,    68,    69,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,
   177,   178,    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,
   187,    -1,    -1,   190,   191,    95,    96,    97,    -1,    -1,
    -1,    -1,    -1,    29,    -1,    31,    32,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   114,   115,    -1,    43,    44,    -1,
    -1,    -1,    -1,    49,    50,    51,    -1,    53,    54,    55,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    78,    79,    -1,    -1,    -1,    -1,   158,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
    96,    97,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,
    -1,    -1,   182,   183,    -1,    -1,    -1,   187,   114,   115,
   190,   191,     4,     5,     6,     7,     8,     9,    10,    -1,
    -1,    13,    14,    15,    16,    17,    18,    19,    20,    21,
    22,    23,    24,    25,    26,    27,    28,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   158,    -1,    46,    47,    48,    -1,    -1,    -1,
    52,    -1,    -1,    -1,    -1,    57,    58,    -1,    60,    61,
    -1,   177,   178,    -1,    -1,    -1,   182,   183,    -1,    -1,
    -1,   187,    70,    71,   190,   191,    -1,    -1,    -1,    -1,
    78,    79,    80,    81,    82,    83,    84,    85,    86,    87,
    88,    89,    90,    91,    92,    93,    94,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   113,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   123,   124,   125,   126,   127,   128,   129,   130,   131,
   132,   133,   134,    -1,   136,   137,   138,   139,    -1,    -1,
    -1,   143,   144,   145,   146,   147,   148,   149,   150,   151,
   152,   153,    -1,    -1,    32,    -1,    34,    35,   160,   161,
   162,   163,   164,    41,    42,    43,    44,    -1,    -1,    -1,
    -1,    49,    50,    51,    -1,    53,    54,    55,    -1,   177,
   178,   179,   180,   181,    -1,    -1,    64,    65,    66,    67,
    68,    69,    -1,    32,    -1,    -1,    -1,    -1,    -1,    -1,
    78,    79,    41,    42,    43,    44,    -1,    -1,    -1,    -1,
    49,    50,    51,    -1,    53,    54,    55,    95,    96,    97,
    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
    69,    -1,    32,    -1,    -1,    -1,   114,   115,    -1,    78,
    79,    -1,    42,    43,    44,    -1,    -1,    -1,    -1,    49,
    50,    51,    -1,    53,    54,    55,    95,    96,    97,    -1,
    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,    69,
    -1,    -1,    -1,    -1,    -1,   114,   115,    -1,    78,    79,
   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    95,    96,    97,    -1,   177,
   178,    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,
    -1,    -1,   190,   191,   114,   115,    -1,    -1,    -1,   158,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,
    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,    -1,
    -1,   190,   191,    -1,    -1,    -1,    -1,    -1,   158,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,
    -1,    32,   182,   183,    -1,    -1,    -1,   187,    -1,    -1,
   190,   191,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
    51,    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    32,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,
    43,    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,
    53,    54,    55,    -1,    95,    96,    97,    -1,    -1,    -1,
    -1,    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,
    -1,    -1,    -1,   114,   115,    78,    79,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   114,   115,    -1,    -1,    -1,    -1,   158,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,
    -1,   182,   183,    -1,    -1,    -1,   187,    -1,    -1,   190,
   191,    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,    32,   182,
   183,    -1,    -1,    -1,   187,    -1,    -1,   190,   191,    43,
    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    53,
    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    64,    65,    66,    67,    68,    69,    -1,    33,    34,    35,
    -1,    -1,    -1,    -1,    78,    79,    -1,    43,    44,    -1,
    -1,    -1,    -1,    49,    50,    51,    -1,    53,    54,    55,
    -1,    95,    96,    97,    -1,    -1,    -1,    -1,    64,    65,
    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
   114,   115,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,   115,
    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   177,   178,    -1,    -1,    -1,   182,   183,
    -1,    -1,    -1,   187,    -1,    -1,   190,   191,    -1,    -1,
    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,   177,   178,    -1,    -1,    -1,   182,   183,    33,    34,
    35,   187,    -1,    -1,   190,   191,    -1,    -1,    43,    44,
    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    53,    54,
    55,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,
    65,    66,    67,    68,    69,    -1,    -1,    34,    35,    -1,
    -1,    -1,    -1,    78,    79,    -1,    43,    44,    -1,    -1,
    -1,    -1,    49,    50,    51,    -1,    53,    54,    55,    -1,
    95,    96,    97,    -1,    -1,    -1,    -1,    64,    65,    66,
    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,   114,
   115,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,    96,
    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,   115,    -1,
    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,   177,   178,    -1,    -1,    -1,   182,   183,    -1,
    -1,    -1,   187,    -1,    -1,   190,   191,    -1,    -1,    -1,
    -1,   158,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   177,   178,    34,    35,    -1,   182,   183,    -1,    -1,    -1,
   187,    43,    44,   190,   191,    -1,    -1,    49,    50,    51,
    -1,    53,    54,    55,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    78,    79,    -1,    43,
    44,    -1,    -1,    -1,    -1,    49,    50,    51,    -1,    53,
    54,    55,    -1,    95,    96,    97,    -1,    -1,    -1,    -1,
    64,    65,    66,    67,    68,    69,    -1,    -1,    -1,    -1,
    -1,    -1,   114,   115,    78,    79,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    95,    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
   114,   115,    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,    -1,
   182,   183,    -1,    -1,    -1,   187,    -1,    -1,   190,   191,
    -1,    -1,    -1,    -1,   158,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   177,   178,    -1,    -1,    -1,   182,   183,
    -1,   185,    -1,   187,    43,    44,   190,   191,    -1,    -1,
    49,    50,    51,    -1,    53,    54,    55,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    64,    65,    66,    67,    68,
    69,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    78,
    79,    -1,    43,    44,    -1,    -1,    -1,    -1,    49,    50,
    51,    -1,    53,    54,    55,    -1,    95,    96,    97,    -1,
    -1,    -1,    -1,    64,    65,    66,    67,    68,    69,    -1,
    -1,    -1,    -1,    -1,    -1,   114,   115,    78,    79,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    95,    96,    97,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   114,   115,    -1,    -1,    -1,    -1,   158,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,
    -1,    -1,    -1,   182,   183,    -1,    -1,    -1,   187,   188,
    -1,   190,   191,    -1,    -1,    -1,    -1,   158,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,   177,   178,    -1,    -1,
    -1,   182,   183,    -1,    -1,    -1,   187,    43,    44,   190,
   191,    -1,    -1,    49,    50,    51,    -1,    53,    54,    55,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    64,    65,
    66,    67,    68,    69,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    78,    79,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    95,
    96,    97,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   114,   115,
    70,    71,    72,    73,    74,    75,    76,    -1,    78,    79,
    80,    81,    82,    83,    84,    85,    86,    87,    88,    89,
    90,    91,    92,    93,    94,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    70,    71,    72,    -1,    74,
    75,    -1,   158,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    89,    90,    91,    92,    93,    94,
    -1,   177,   178,    -1,    -1,    -1,   182,   183,    -1,    -1,
    -1,   187,    -1,    -1,   190,   191,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,   173,   174,   175,   176,   177,   178,   179,
   180,   181,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,
    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,    -1,   174,
   175,   176,   177,   178,   179,   180,   181
};
/* -*-C-*-  Note some compilers choke on comments on `#line' lines.  */
#line 3 "bison.simple"
/* This file comes from bison-1.27.  */

/* Skeleton output parser for bison,
   Copyright (C) 1984, 1989, 1990 Free Software Foundation, Inc.

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; either version 2, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place - Suite 330,
   Boston, MA 02111-1307, USA.  */

/* As a special exception, when this file is copied by Bison into a
   Bison output file, you may use that output file without restriction.
   This special exception was added by the Free Software Foundation
   in version 1.24 of Bison.  */

/* This is the parser code that is written into each bison parser
  when the %semantic_parser declaration is not specified in the grammar.
  It was written by Richard Stallman by simplifying the hairy parser
  used when %semantic_parser is specified.  */

#ifndef YYSTACK_USE_ALLOCA
#ifdef alloca
#define YYSTACK_USE_ALLOCA
#else /* alloca not defined */
#ifdef __GNUC__
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#else /* not GNU C.  */
#if (!defined (__STDC__) && defined (sparc)) || defined (__sparc__) || defined (__sparc) || defined (__sgi) || (defined (__sun) && defined (__i386))
#define YYSTACK_USE_ALLOCA
#include <alloca.h>
#else /* not sparc */
/* We think this test detects Watcom and Microsoft C.  */
/* This used to test MSDOS, but that is a bad idea
   since that symbol is in the user namespace.  */
#if (defined (_MSDOS) || defined (_MSDOS_)) && !defined (__TURBOC__)
#if 0 /* No need for malloc.h, which pollutes the namespace;
	 instead, just don't use alloca.  */
#include <malloc.h>
#endif
#else /* not MSDOS, or __TURBOC__ */
#if defined(_AIX)
/* I don't know what this was needed for, but it pollutes the namespace.
   So I turned it off.   rms, 2 May 1997.  */
/* #include <malloc.h>  */
 #pragma alloca
#define YYSTACK_USE_ALLOCA
#else /* not MSDOS, or __TURBOC__, or _AIX */
#if 0
#ifdef __hpux /* haible@ilog.fr says this works for HPUX 9.05 and up,
		 and on HPUX 10.  Eventually we can turn this on.  */
#define YYSTACK_USE_ALLOCA
#define alloca __builtin_alloca
#endif /* __hpux */
#endif
#endif /* not _AIX */
#endif /* not MSDOS, or __TURBOC__ */
#endif /* not sparc */
#endif /* not GNU C */
#endif /* alloca not defined */
#endif /* YYSTACK_USE_ALLOCA not defined */

#ifdef YYSTACK_USE_ALLOCA
#define YYSTACK_ALLOC alloca
#else
#define YYSTACK_ALLOC malloc
#endif

/* Note: there must be only one dollar sign in this file.
   It is replaced by the list of actions, each action
   as one case of the switch.  */

#define yyerrok		(yyerrstatus = 0)
#define yyclearin	(yychar = YYEMPTY)
#define YYEMPTY		-2
#define YYEOF		0
#define YYACCEPT	goto yyacceptlab
#define YYABORT 	goto yyabortlab
#define YYERROR		goto yyerrlab1
/* Like YYERROR except do call yyerror.
   This remains here temporarily to ease the
   transition to the new meaning of YYERROR, for GCC.
   Once GCC version 2 has supplanted version 1, this can go.  */
#define YYFAIL		goto yyerrlab
#define YYRECOVERING()  (!!yyerrstatus)
#define YYBACKUP(token, value) \
do								\
  if (yychar == YYEMPTY && yylen == 1)				\
    { yychar = (token), yylval = (value);			\
      yychar1 = YYTRANSLATE (yychar);				\
      YYPOPSTACK;						\
      goto yybackup;						\
    }								\
  else								\
    { yyerror ("syntax error: cannot back up"); YYERROR; }	\
while (0)

#define YYTERROR	1
#define YYERRCODE	256

#ifndef YYPURE
#define YYLEX		yylex()
#endif

#ifdef YYPURE
#ifdef YYLSP_NEEDED
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, &yylloc, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval, &yylloc)
#endif
#else /* not YYLSP_NEEDED */
#ifdef YYLEX_PARAM
#define YYLEX		yylex(&yylval, YYLEX_PARAM)
#else
#define YYLEX		yylex(&yylval)
#endif
#endif /* not YYLSP_NEEDED */
#endif

/* If nonreentrant, generate the variables here */

#ifndef YYPURE

int	yychar;			/*  the lookahead symbol		*/
YYSTYPE	yylval;			/*  the semantic value of the		*/
				/*  lookahead symbol			*/

#ifdef YYLSP_NEEDED
YYLTYPE yylloc;			/*  location data for the lookahead	*/
				/*  symbol				*/
#endif

int yynerrs;			/*  number of parse errors so far       */
#endif  /* not YYPURE */

#if YYDEBUG != 0
int yydebug;			/*  nonzero means print parse trace	*/
/* Since this is uninitialized, it does not stop multiple parsers
   from coexisting.  */
#endif

/*  YYINITDEPTH indicates the initial size of the parser's stacks	*/

#ifndef	YYINITDEPTH
#define YYINITDEPTH 200
#endif

/*  YYMAXDEPTH is the maximum size the stacks can grow to
    (effective only if the built-in stack extension method is used).  */

#if YYMAXDEPTH == 0
#undef YYMAXDEPTH
#endif

#ifndef YYMAXDEPTH
#define YYMAXDEPTH 10000
#endif

/* Define __yy_memcpy.  Note that the size argument
   should be passed with type unsigned int, because that is what the non-GCC
   definitions require.  With GCC, __builtin_memcpy takes an arg
   of type size_t, but it can handle unsigned int.  */

#if __GNUC__ > 1		/* GNU C and GNU C++ define this.  */
#define __yy_memcpy(TO,FROM,COUNT)	__builtin_memcpy(TO,FROM,COUNT)
#else				/* not GNU C or C++ */
#ifndef __cplusplus

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (to, from, count)
     char *to;
     char *from;
     unsigned int count;
{
  register char *f = from;
  register char *t = to;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#else /* __cplusplus */

/* This is the most reliable way to avoid incompatibilities
   in available built-in functions on various systems.  */
static void
__yy_memcpy (char *to, char *from, unsigned int count)
{
  register char *t = to;
  register char *f = from;
  register int i = count;

  while (i-- > 0)
    *t++ = *f++;
}

#endif
#endif

#line 216 "bison.simple"

/* The user can define YYPARSE_PARAM as the name of an argument to be passed
   into yyparse.  The argument should have type void *.
   It should actually point to an object.
   Grammar actions can access the variable by casting it
   to the proper pointer type.  */

#ifdef YYPARSE_PARAM
#ifdef __cplusplus
#define YYPARSE_PARAM_ARG void *YYPARSE_PARAM
#define YYPARSE_PARAM_DECL
#else /* not __cplusplus */
#define YYPARSE_PARAM_ARG YYPARSE_PARAM
#define YYPARSE_PARAM_DECL void *YYPARSE_PARAM;
#endif /* not __cplusplus */
#else /* not YYPARSE_PARAM */
#define YYPARSE_PARAM_ARG
#define YYPARSE_PARAM_DECL
#endif /* not YYPARSE_PARAM */

/* Prevent warning if -Wstrict-prototypes.  */
#ifdef __GNUC__
#ifdef YYPARSE_PARAM
int yyparse (void *);
#else
int yyparse (void);
#endif
#endif

int
yyparse(YYPARSE_PARAM_ARG)
     YYPARSE_PARAM_DECL
{
  register int yystate;
  register int yyn;
  register short *yyssp;
  register YYSTYPE *yyvsp;
  int yyerrstatus;	/*  number of tokens to shift before error messages enabled */
  int yychar1 = 0;		/*  lookahead token as an internal (translated) token number */

  short	yyssa[YYINITDEPTH];	/*  the state stack			*/
  YYSTYPE yyvsa[YYINITDEPTH];	/*  the semantic value stack		*/

  short *yyss = yyssa;		/*  refer to the stacks thru separate pointers */
  YYSTYPE *yyvs = yyvsa;	/*  to allow yyoverflow to reallocate them elsewhere */

#ifdef YYLSP_NEEDED
  YYLTYPE yylsa[YYINITDEPTH];	/*  the location stack			*/
  YYLTYPE *yyls = yylsa;
  YYLTYPE *yylsp;

#define YYPOPSTACK   (yyvsp--, yyssp--, yylsp--)
#else
#define YYPOPSTACK   (yyvsp--, yyssp--)
#endif

  int yystacksize = YYINITDEPTH;
  int yyfree_stacks = 0;

#ifdef YYPURE
  int yychar;
  YYSTYPE yylval;
  int yynerrs;
#ifdef YYLSP_NEEDED
  YYLTYPE yylloc;
#endif
#endif

  YYSTYPE yyval;		/*  the variable used to return		*/
				/*  semantic values from the action	*/
				/*  routines				*/

  int yylen;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Starting parse\n");
#endif

  yystate = 0;
  yyerrstatus = 0;
  yynerrs = 0;
  yychar = YYEMPTY;		/* Cause a token to be read.  */

  /* Initialize stack pointers.
     Waste one element of value and location stack
     so that they stay on the same level as the state stack.
     The wasted elements are never initialized.  */

  yyssp = yyss - 1;
  yyvsp = yyvs;
#ifdef YYLSP_NEEDED
  yylsp = yyls;
#endif

/* Push a new state, which is found in  yystate  .  */
/* In all cases, when you get here, the value and location stacks
   have just been pushed. so pushing a state here evens the stacks.  */
yynewstate:

  *++yyssp = yystate;

  if (yyssp >= yyss + yystacksize - 1)
    {
      /* Give user a chance to reallocate the stack */
      /* Use copies of these so that the &'s don't force the real ones into memory. */
      YYSTYPE *yyvs1 = yyvs;
      short *yyss1 = yyss;
#ifdef YYLSP_NEEDED
      YYLTYPE *yyls1 = yyls;
#endif

      /* Get the current used size of the three stacks, in elements.  */
      int size = yyssp - yyss + 1;

#ifdef yyoverflow
      /* Each stack pointer address is followed by the size of
	 the data in use in that stack, in bytes.  */
#ifdef YYLSP_NEEDED
      /* This used to be a conditional around just the two extra args,
	 but that might be undefined if yyoverflow is a macro.  */
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yyls1, size * sizeof (*yylsp),
		 &yystacksize);
#else
      yyoverflow("parser stack overflow",
		 &yyss1, size * sizeof (*yyssp),
		 &yyvs1, size * sizeof (*yyvsp),
		 &yystacksize);
#endif

      yyss = yyss1; yyvs = yyvs1;
#ifdef YYLSP_NEEDED
      yyls = yyls1;
#endif
#else /* no yyoverflow */
      /* Extend the stack our own way.  */
      if (yystacksize >= YYMAXDEPTH)
	{
	  yyerror("parser stack overflow");
	  if (yyfree_stacks)
	    {
	      free (yyss);
	      free (yyvs);
#ifdef YYLSP_NEEDED
	      free (yyls);
#endif
	    }
	  return 2;
	}
      yystacksize *= 2;
      if (yystacksize > YYMAXDEPTH)
	yystacksize = YYMAXDEPTH;
#ifndef YYSTACK_USE_ALLOCA
      yyfree_stacks = 1;
#endif
      yyss = (short *) YYSTACK_ALLOC (yystacksize * sizeof (*yyssp));
      __yy_memcpy ((char *)yyss, (char *)yyss1,
		   size * (unsigned int) sizeof (*yyssp));
      yyvs = (YYSTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yyvsp));
      __yy_memcpy ((char *)yyvs, (char *)yyvs1,
		   size * (unsigned int) sizeof (*yyvsp));
#ifdef YYLSP_NEEDED
      yyls = (YYLTYPE *) YYSTACK_ALLOC (yystacksize * sizeof (*yylsp));
      __yy_memcpy ((char *)yyls, (char *)yyls1,
		   size * (unsigned int) sizeof (*yylsp));
#endif
#endif /* no yyoverflow */

      yyssp = yyss + size - 1;
      yyvsp = yyvs + size - 1;
#ifdef YYLSP_NEEDED
      yylsp = yyls + size - 1;
#endif

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Stack size increased to %d\n", yystacksize);
#endif

      if (yyssp >= yyss + yystacksize - 1)
	YYABORT;
    }

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Entering state %d\n", yystate);
#endif

  goto yybackup;
 yybackup:

/* Do appropriate processing given the current state.  */
/* Read a lookahead token if we need one and don't already have one.  */
/* yyresume: */

  /* First try to decide what to do without reference to lookahead token.  */

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yydefault;

  /* Not known => get a lookahead token if don't already have one.  */

  /* yychar is either YYEMPTY or YYEOF
     or a valid token in external form.  */

  if (yychar == YYEMPTY)
    {
#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Reading a token: ");
#endif
      yychar = YYLEX;
    }

  /* Convert token to internal form (in yychar1) for indexing tables with */

  if (yychar <= 0)		/* This means end of input. */
    {
      yychar1 = 0;
      yychar = YYEOF;		/* Don't call YYLEX any more */

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Now at end of input.\n");
#endif
    }
  else
    {
      yychar1 = YYTRANSLATE(yychar);

#if YYDEBUG != 0
      if (yydebug)
	{
	  fprintf (stderr, "Next token is %d (%s", yychar, yytname[yychar1]);
	  /* Give the individual parser a way to print the precise meaning
	     of a token, for further debugging info.  */
#ifdef YYPRINT
	  YYPRINT (stderr, yychar, yylval);
#endif
	  fprintf (stderr, ")\n");
	}
#endif
    }

  yyn += yychar1;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != yychar1)
    goto yydefault;

  yyn = yytable[yyn];

  /* yyn is what to do for this token type in this state.
     Negative => reduce, -yyn is rule number.
     Positive => shift, yyn is new state.
       New state is final state => don't bother to shift,
       just return success.
     0, or most negative number => error.  */

  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrlab;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrlab;

  if (yyn == YYFINAL)
    YYACCEPT;

  /* Shift the lookahead token.  */

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting token %d (%s), ", yychar, yytname[yychar1]);
#endif

  /* Discard the token being shifted unless it is eof.  */
  if (yychar != YYEOF)
    yychar = YYEMPTY;

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  /* count tokens shifted since error; after three, turn off error status.  */
  if (yyerrstatus) yyerrstatus--;

  yystate = yyn;
  goto yynewstate;

/* Do the default action for the current state.  */
yydefault:

  yyn = yydefact[yystate];
  if (yyn == 0)
    goto yyerrlab;

/* Do a reduction.  yyn is the number of a rule to reduce with.  */
yyreduce:
  yylen = yyr2[yyn];
  if (yylen > 0)
    yyval = yyvsp[1-yylen]; /* implement default value of the action */

#if YYDEBUG != 0
  if (yydebug)
    {
      int i;

      fprintf (stderr, "Reducing via rule %d (line %d), ",
	       yyn, yyrline[yyn]);

      /* Print the symbols being reduced, and their result.  */
      for (i = yyprhs[yyn]; yyrhs[i] > 0; i++)
	fprintf (stderr, "%s ", yytname[yyrhs[i]]);
      fprintf (stderr, " -> %s\n", yytname[yyr1[yyn]]);
    }
#endif


  switch (yyn) {

case 3:
#line 2304 "zmac.y"
{ 
		// An identfier without a colon all by itself on a line
		// will be interpreted as a label.  But there's a very
		// good chance it is a misspelling of an instruction or
		// pseudo-op name creating silent errors.  Since the condition
		// is unusual we print a warning.  Unless it is followed by
		// a colon in which case there's no ambiguity.
		if (yyvsp[-1].itemptr && !firstcol && coloncnt == 0 && outpass) {
			fprintf(stderr, "%s(%d): warning: '%s' treated as label (instruction typo?)\n",
				src_name[now_in], linein[now_in], yyvsp[-1].itemptr->i_string);
			fprintf(stderr, "\tAdd a colon or move to first column to stop this warning.\n");
		}

		if (yyvsp[-1].itemptr) list(dollarsign);
		else  list1();
	;
    break;}
case 4:
#line 2321 "zmac.y"
{ list_dollarsign = 1; ;
    break;}
case 5:
#line 2321 "zmac.y"
{
		list(list_dollarsign ? dollarsign : list_addr);
	;
    break;}
case 6:
#line 2325 "zmac.y"
{
		do_equ(yyvsp[-4].itemptr, yyvsp[-1].exprptr, 1);
		if (yyvsp[-3].ival == 2)
			yyvsp[-4].itemptr->i_scope |= SCOPE_PUBLIC;
	;
    break;}
case 7:
#line 2331 "zmac.y"
{
		do_equ(yyvsp[-4].itemptr, expr_num(keyword_index(yyvsp[-1].itemptr)), 1);
		yyvsp[-4].itemptr->i_scope |= SCOPE_ALIAS;
		if (yyvsp[-3].ival == 2)
			yyvsp[-4].itemptr->i_scope |= SCOPE_PUBLIC;
	;
    break;}
case 8:
#line 2338 "zmac.y"
{
		do_defl(yyvsp[-4].itemptr, yyvsp[-1].exprptr, 1); // TODO: is '=' equate or defl?
		// I don't even recall what assembler I saw that allows '='
		// Not MACR0-80.  Not MRAS.  Not MAC.
		// I choose "defl" since it works so nicely with +=, etc.
		if (yyvsp[-3].ival == 2)
			yyvsp[-4].itemptr->i_scope |= SCOPE_PUBLIC;
	;
    break;}
case 9:
#line 2347 "zmac.y"
{
		do_defl(yyvsp[-3].itemptr, yyvsp[-1].exprptr, 1);
	;
    break;}
case 10:
#line 2351 "zmac.y"
{
		do_defl(yyvsp[-4].itemptr, expr_mk(expr_var(yyvsp[-4].itemptr), yyvsp[-3].ival, yyvsp[-1].exprptr), 1);
	;
    break;}
case 11:
#line 2355 "zmac.y"
{
		do_defl(yyvsp[-3].itemptr, expr_mk(expr_var(yyvsp[-3].itemptr), '+', expr_num(1)), 1);
	;
    break;}
case 12:
#line 2359 "zmac.y"
{
		do_defl(yyvsp[-3].itemptr, expr_mk(expr_var(yyvsp[-3].itemptr), '-', expr_num(1)), 1);
	;
    break;}
case 13:
#line 2363 "zmac.y"
{
		int val3 = yyvsp[-3].exprptr->e_value;
		int val5 = yyvsp[-1].exprptr->e_value;
		expr_reloc_check(yyvsp[-3].exprptr);
		expr_reloc_check(yyvsp[-1].exprptr);
		expr_scope_same(yyvsp[-3].exprptr, yyvsp[-1].exprptr);
		switch (yyvsp[-5].itemptr->i_token) {
		case UNDECLARED: case DEFLED:
			yyvsp[-5].itemptr->i_token = DEFLED;
			yyvsp[-5].itemptr->i_pass = npass;
			yyvsp[-5].itemptr->i_scope |= yyvsp[-3].exprptr->e_scope;
			if (yyvsp[-4].itemptr->i_value)	/* max */
				list(yyvsp[-5].itemptr->i_value = (val3 > val5? val3:val5));
			else list(yyvsp[-5].itemptr->i_value = (val3 < val5? val3:val5));
			break;
		default:
			err[mflag]++;
			yyvsp[-5].itemptr->i_token = MULTDEF;
			yyvsp[-5].itemptr->i_pass = npass;
			list(yyvsp[-5].itemptr->i_value);
		}
		expr_free(yyvsp[-3].exprptr);
		expr_free(yyvsp[-1].exprptr);
	;
    break;}
case 14:
#line 2388 "zmac.y"
{
		do_if(yyvsp[-1].exprptr);
	;
    break;}
case 15:
#line 2392 "zmac.y"
{
		expr_number_check(yyvsp[-1].exprptr);
		do_if_value(!yyvsp[-1].exprptr->e_value);
		expr_free(yyvsp[-1].exprptr);
	;
    break;}
case 16:
#line 2398 "zmac.y"
{
		do_if_value(npass == 1);
	;
    break;}
case 17:
#line 2402 "zmac.y"
{
		do_if_value(outpass);
	;
    break;}
case 18:
#line 2406 "zmac.y"
{
		// Unpleasant duplication of IF_TK work.
		do_if(expr_mk(yyvsp[-3].exprptr, yyvsp[-4].itemptr->i_value , yyvsp[-1].exprptr));
	;
    break;}
case 19:
#line 2412 "zmac.y"
{
		struct item *ip = locate(tempbuf);
		int declared = ip && ip->i_pass == npass;
		int value = declared == yyvsp[-4].itemptr->i_value;
		do_if_value(value);
	;
    break;}
case 20:
#line 2419 "zmac.y"
{
		char saveopt;

		/* FIXME: it would be nice to spot repeated ELSEs, but how? */
		*ifptr = !*ifptr;
		saveopt = fopt;
		fopt = 1;
		list1();
		fopt = saveopt;
	;
    break;}
case 21:
#line 2430 "zmac.y"
{
		if (ifptr == ifstack) err[bflag]++;
		else --ifptr;
		list1();
	;
    break;}
case 22:
#line 2436 "zmac.y"
{
		list(dollarsign);
		do_end(NULL);
	;
    break;}
case 23:
#line 2441 "zmac.y"
{
		list(yyvsp[-1].exprptr->e_value);
		do_end(yyvsp[-1].exprptr);
	;
    break;}
case 24:
#line 2446 "zmac.y"
{
		expr_number_check(yyvsp[-1].exprptr);
		if (yyvsp[-1].exprptr->e_value < 0) err[vflag]++;
		if (yyvsp[-1].exprptr->e_value > 0) {
			if (!phaseflag) {
				list(dollarsign);
				flushbin();
				flushoth();
				dollarsign += yyvsp[-1].exprptr->e_value;
				olddollar += yyvsp[-1].exprptr->e_value;
				oldothdollar += yyvsp[-1].exprptr->e_value;
				emit_addr += yyvsp[-1].exprptr->e_value;
				advance_segment(yyvsp[-1].exprptr->e_value);
				putrelcmd(RELCMD_SETLOC);
				putrelsegref(segment, seg_pos[segment]);
			}
			else
				dc(yyvsp[-1].exprptr->e_value, 0);
		}
		else
			list1();

		expr_free(yyvsp[-1].exprptr);
	;
    break;}
case 25:
#line 2471 "zmac.y"
{
		expr_number_check(yyvsp[-3].exprptr);
		expr_number_check(yyvsp[-1].exprptr);
		if (yyvsp[-3].exprptr->e_value < 0) err[vflag]++;
		if (yyvsp[-1].exprptr->e_value < -128 || yyvsp[-1].exprptr->e_value > 127) err[vflag]++;
		if (yyvsp[-3].exprptr->e_value > 0) {
			dc(yyvsp[-3].exprptr->e_value, yyvsp[-1].exprptr->e_value);
		}
		else
			list1();

		expr_free(yyvsp[-3].exprptr);
		expr_free(yyvsp[-1].exprptr);
	;
    break;}
case 26:
#line 2486 "zmac.y"
{ emit(1, E_DATA, expr_num(yyvsp[-1].ival | 0x80)); list(dollarsign); ;
    break;}
case 27:
#line 2488 "zmac.y"
{ emit(1, E_DATA, expr_num(yyvsp[-1].ival)); emit(1, E_DATA, expr_num((yyvsp[-1].ival >> 8) | 0x80)); list(dollarsign); ;
    break;}
case 28:
#line 2491 "zmac.y"
{
			for (cp = yyvsp[-1].cval; *cp != '\0'; cp++)
				if (!cp[1])
					emit(1, E_DATA, expr_num(*cp | 0x80));
				else
					emit(1, E_DATA, expr_num(*cp));

			list(dollarsign);
		;
    break;}
case 29:
#line 2502 "zmac.y"
{
			expr_number_check(yyvsp[-3].exprptr);
			expr_number_check(yyvsp[-1].exprptr);
			dc(yyvsp[-3].exprptr->e_value, yyvsp[-1].exprptr->e_value);
			expr_free(yyvsp[-3].exprptr);
			expr_free(yyvsp[-1].exprptr);
		;
    break;}
case 30:
#line 2510 "zmac.y"
{
		list1();
		switch (yyvsp[-4].itemptr->i_value) {

		case PSTITL:	/* title */
			lineptr = linebuf;
			cp = tempbuf;
			title = titlespace;
			while ((*title++ = *cp++) && (title < &titlespace[TITLELEN]));
			*title = 0;
			title = titlespace;
			break;

		case PSRSYM:	/* rsym */
			if (pass2) break;
			insymtab(tempbuf);
			break;

		case PSWSYM:	/* wsym */
			writesyms = malloc(strlen(tempbuf)+1);
			strcpy(writesyms, tempbuf);
			break;
		case PSINC:	/* include file */
			if (mras) {
				// Allow for FILE/EXT; TRS-80 used / for extension.
				char *slash = strchr(tempbuf, '/');
				// Must have only one slash and short extension.
				if (slash && !strchr(slash + 1, '/') &&
					strlen(slash + 1) <= 3)
				{
					*slash = '.';
				}

				// MRAS appends "asm" suffix if not present.
				if (!strchr(tempbuf, '.'))
					strcat(tempbuf, ".asm");
			}
			next_source(tempbuf, 1);
			break ;
		case PSIMPORT:	/* import file */
			next_source(tempbuf, 0);
			break;
		case PSMACLIB:
			strcat(tempbuf, ".lib");
			next_source(tempbuf, 1);
			break;
		case PSCMN:
			common_block(tempbuf);
			break;
		}
	;
    break;}
case 31:
#line 2562 "zmac.y"
{
		if (yyvsp[-3].itemptr->i_value == PSCMN) {
			common_block(" ");
		}
		else {
			fprintf(stderr, "Missing argument of '%s'\n", yyvsp[-3].itemptr->i_string);
			err[fflag]++;
		}
		list1();
	;
    break;}
case 32:
#line 2573 "zmac.y"
{
		incbin(tempbuf);
	;
    break;}
case 33:
#line 2577 "zmac.y"
{ raw = 1; ;
    break;}
case 34:
#line 2577 "zmac.y"
{
		int quote = 0;
		char *p, *q;
		switch (yyvsp[-2].itemptr->i_value) {
		case SPTITL:
			cp = tempbuf;
			title = titlespace;
			if (*cp == '\'' || *cp == '"')
				quote = *cp++;
			while ((*title++ = *cp++) && (title < &titlespace[TITLELEN]));
			if (quote && title > titlespace + 1 && title[-2] == quote)
				title[-2] = '\0';
			title = titlespace;
			list1();
			break;
		case SPSBTL:
			cp = tempbuf;
			subtitle = subtitlespace;
			if (*cp == '\'' || *cp == '"')
				quote = *cp++;
			while ((*subtitle++ = *cp++) && (subtitle < &subtitlespace[TITLELEN]));
			if (quote && subtitle > subtitlespace + 1 && subtitle[-2] == quote)
				subtitle[-2] = '\0';
			subtitle = subtitlespace;
			list1();
			break;
		case SPNAME:
			// Drop surrounding ('') if present
			p = tempbuf;
			q = strchr(tempbuf, '\0') - 1;
			if (*p == '(' && *q == ')' && q > p) p++, q--;
			if (*p == '\'' && *q == '\'' && q > p) p++, q--;
			q[1] = '\0';
			strncpy(progname, p, sizeof progname);
			progname[sizeof progname - 1] = '\0';
			list1();
			break;
		case SPCOM:
			quote = *tempbuf;
			list1();
			for (;;) {
				raw = 1;
				yychar = yylex();
				list1();
				if (yychar == 0)
					break;
				if (*tempbuf == quote) {
					yychar = yylex();
					break;
				}
			}
			break;

		case SPPRAGMA:
			if (strncmp(tempbuf, "bds", 3) == 0 && fbds && outpass) {
				fprintf(fbds, "%s\n", tempbuf + 4);
			}
			if (strncmp(tempbuf, "mds", 3) == 0 && fmds && outpass) {
				fprintf(fmds, "%s\n", tempbuf + 4);
			}
			list1();
			break;

		case SPRINTX:
			p = tempbuf;
			quote = *p++;
			q = strchr(p, quote);
			printf("%.*s\n", (int)(q - p), p);
			break;
		}
	;
    break;}
case 35:
#line 2649 "zmac.y"
{
		dolopt(yyvsp[-1].itemptr, 1); ;
    break;}
case 36:
#line 2652 "zmac.y"
{
		int enable = yyvsp[-2].exprptr->e_value;

		if (mras) {
			if (ci_strcmp(tempbuf, "on") == 0)
				enable = 1;
			else if (ci_strcmp(tempbuf, "off") == 0)
				enable = -1;
			else {
				fprintf(stderr, "LIST not given 'on' or 'off'\n");
				err[fflag]++;
				list(dollarsign);
				goto dolopt_done;
			}
		}
		else {
			expr_number_check(yyvsp[-2].exprptr);
			expr_free(yyvsp[-2].exprptr);
		}

		dolopt(yyvsp[-4].itemptr, enable);

	dolopt_done: ;
	;
    break;}
case 37:
#line 2677 "zmac.y"
{
		expr_number_check(yyvsp[-1].exprptr);
		jopt = !!yyvsp[-1].exprptr->e_value;
		list1();
		expr_free(yyvsp[-1].exprptr);
	;
    break;}
case 38:
#line 2684 "zmac.y"
{
		expr_number_check(yyvsp[-1].exprptr);
		JPopt = !!yyvsp[-1].exprptr->e_value;
		list1();
		expr_free(yyvsp[-1].exprptr);
	;
    break;}
case 39:
#line 2691 "zmac.y"
{
		list1();
	;
    break;}
case 40:
#line 2695 "zmac.y"
{
		list1();
	;
    break;}
case 41:
#line 2699 "zmac.y"
{
		char *p = strchr(modstr, '\0') - 1;
		for (; p >= modstr; p--) {
			(*p)++;
			if (*p < 'Z')
				break;
			*p = 'A';
		}
		list1();
	;
    break;}
case 42:
#line 2710 "zmac.y"
{
		if (relopt && segment != yyvsp[-1].itemptr->i_value) {
			segment = yyvsp[-1].itemptr->i_value;
			segchange = 1;
			dollarsign = seg_pos[yyvsp[-1].itemptr->i_value];
		}
		list1();
	;
    break;}
case 43:
#line 2719 "zmac.y"
{
		z80 = yyvsp[-1].itemptr->i_value;
		list1();
	;
    break;}
case 44:
#line 2724 "zmac.y"
{ param_parse = 1; ;
    break;}
case 45:
#line 2724 "zmac.y"
{
		param_parse = 0;
		yyvsp[-4].itemptr->i_token = MNAME;
		yyvsp[-4].itemptr->i_pass = npass;
		yyvsp[-4].itemptr->i_value = mfptr;
		if (keyword(yyvsp[-4].itemptr->i_string) && !driopt) {
			sprintf(detail, "Macro '%s' will override the built-in '%s'",
				yyvsp[-4].itemptr->i_string, yyvsp[-4].itemptr->i_string);
			errwarn(warn_general, detail);
		}
#ifdef M_DEBUG
		fprintf (stderr, "%s(%d) [UNDECLARED MACRO %s]\n",
			src_name[now_in], linein[now_in], yyvsp[-4].itemptr->i_string);
#endif
		list1();
	;
    break;}
case 46:
#line 2740 "zmac.y"
{
		mlex_list_on += !iopt;
		mfseek(mfile, (long)mfptr, 0);
		mlex(yyvsp[0].cval);
		mlex_list_on -= !iopt;
		parm_number = 0;
	;
    break;}
case 47:
#line 2748 "zmac.y"
{ arg_state.macarg = 1; ;
    break;}
case 48:
#line 2748 "zmac.y"
{
#ifdef M_DEBUG
		fprintf (stderr, "%s(%d) [MNAME %s]\n",
			src_name[now_in], linein[now_in], yyvsp[-4].itemptr->i_string);
#endif
		yyvsp[-4].itemptr->i_uses++ ;
		arg_reset();
		delayed_list(dollarsign);
		expptr++;
		est = est2;
		est2 = NULL; // GWP - this may leak, but it avoids double-free crashes
		est[FLOC].value = floc;
		est[TEMPNUM].value = exp_number++;
		est[MIF].param = ifptr;
		est[REPNUM].value = 0;
		est[MSTR].param = NULL;
		est[MNUMPAR].value = parm_number;
		floc = yyvsp[-4].itemptr->i_value;
		parm_number = 0;
		mfseek(mfile, (long)floc, 0);
	;
    break;}
case 49:
#line 2770 "zmac.y"
{
		expr_reloc_check(yyvsp[-2].exprptr);
		// MRAS compat would require treating the repeat count
		// as a byte value with 0 == 256.
		at_least_once = yyvsp[-2].exprptr->e_value > 0;

		if (at_least_once)
			delayed_list1();
		else
			list1();

		arg_reset();
	;
    break;}
case 50:
#line 2783 "zmac.y"
{
		int pos = mfptr;
		mfseek(mfile, (long)mfptr, 0);
		mlex(yyvsp[0].cval);
		parm_number = 0;

		if (at_least_once) {
			expptr++;
			est = est2;
			est2 = NULL;
			est[FLOC].value = floc;
			est[TEMPNUM].value = exp_number++;
			est[MIF].param = ifptr;
			est[REPNUM].value = yyvsp[-4].exprptr->e_value - 1;
			est[MSTART].value = pos;
			est[MSTR].param = NULL;
			floc = pos;
			mfseek(mfile, (long)floc, 0);
		}
	;
    break;}
case 51:
#line 2804 "zmac.y"
{ parm_number = 0; ;
    break;}
case 52:
#line 2805 "zmac.y"
{
		at_least_once = est2[0].param[0];

		if (at_least_once)
			delayed_list1();
		else
			list1();
	;
    break;}
case 53:
#line 2813 "zmac.y"
{
		int pos = mfptr;

		mfseek(mfile, (long)mfptr, 0);
		mlex(yyvsp[0].cval);

		parm_number = 0;

		if (at_least_once) {
			expptr++;
			est = est2;
			est2 = NULL;
			est[FLOC].value = floc;
			est[TEMPNUM].value = exp_number++;
			est[MIF].param = ifptr;
			est[REPNUM].value = 0;
			est[MSTART].value = pos;
			est[MSTR].param = est[0].param;
			est[0].param = malloc(2);
			est[0].param[0] = est[MSTR].param[0];
			est[0].param[1] = '\0';
			floc = pos;
			mfseek(mfile, (long)floc, 0);
		}
	;
    break;}
case 54:
#line 2839 "zmac.y"
{ parm_number = 0; ;
    break;}
case 55:
#line 2840 "zmac.y"
{
		// if the sub list is not empty
		at_least_once = est2[0].param[0] && est2[0].param[0] != ';'
			&& est2[0].param[0] != '\n';

		if (at_least_once)
			delayed_list1();
		else
			list1();
	;
    break;}
case 56:
#line 2850 "zmac.y"
{
		int pos = mfptr;
		mfseek(mfile, (long)mfptr, 0);
		mlex(yyvsp[0].cval);

		parm_number = 0;
		if (at_least_once) {
			expptr++;
			est = est2;
			est2 = NULL;
			est[FLOC].value = floc;
			est[TEMPNUM].value = exp_number++;
			est[MIF].param = ifptr;
			est[REPNUM].value = -1;
			est[MSTART].value = pos;
			est[MSTR].param = NULL;

			est[MARGP].ap = malloc(sizeof *est[MARGP].ap);
			est[MARGP].ap->arg = malloc(TEMPBUFSIZE);
			est[MARGP].ap->argsize = TEMPBUFSIZE;
			est[MARGP].ap->getch = str_getch;
			est[MARGP].ap->user_ptr = est[0].param;
			est[MARGP].ap->user_int = 0;
			est[MARGP].ap->user_peek = -1;
			est[MARGP].ap->peek = &est[MARGP].ap->user_peek;
			est[MARGP].ap->macarg = 0;
			est[MARGP].ap->didarg = 0;
			est[MARGP].ap->numarg = 0;

			est[0].param = est[MARGP].ap->arg;
			getarg(est[MARGP].ap);

			floc = pos;
			mfseek(mfile, (long)floc, 0);
		}
	;
    break;}
case 57:
#line 2887 "zmac.y"
{
		// XXX - popsi() is not safe, There is type-specific cleanup.
		//  But for now...
		// popsi() must be made safe as others use it.
		list1();
		popsi();
	;
    break;}
case 58:
#line 2895 "zmac.y"
{
		err[warn_notimpl]++;
		list1();
	;
    break;}
case 59:
#line 2900 "zmac.y"
{
		err[warn_notimpl]++;
		list1();
	;
    break;}
case 60:
#line 2905 "zmac.y"
{
		err[warn_notimpl]++;
		list1();
	;
    break;}
case 61:
#line 2910 "zmac.y"
{
		err[fflag]++;
		arg_reset();
		parm_number = 0;
		param_parse = 0;

		if (est2)
		{
			int i;
			for (i=0; i<PARMMAX; i++) {
				if (est2[i].param) {
#ifdef M_DEBUG
	fprintf (stderr, "[Freeing2 arg%u(%p)]\n", i, est2[i].param),
#endif
					free(est2[i].param);
				}
			}
			free(est2);
			est2 = NULL;
		}

		while(yychar != '\n' && yychar != '\0') yychar = yylex();
		list(dollarsign);
		yyclearin;yyerrok;
	;
    break;}
case 62:
#line 2938 "zmac.y"
{ yyval.ival = 0; ;
    break;}
case 63:
#line 2940 "zmac.y"
{ yyval.ival = 1; ;
    break;}
case 64:
#line 2942 "zmac.y"
{ yyval.ival = 2; ;
    break;}
case 65:
#line 2947 "zmac.y"
{	label = yyval.itemptr = NULL;	;
    break;}
case 66:
#line 2949 "zmac.y"
{
		coloncnt = yyvsp[0].ival;
		itemcpy(&pristine_label, yyvsp[-1].itemptr);
		label = coloncnt == 0 ? yyvsp[-1].itemptr : NULL;
		if (!phaseflag)
			yyvsp[-1].itemptr->i_scope |= segment;

		if (yyvsp[0].ival == 2)
			yyvsp[-1].itemptr->i_scope |= SCOPE_PUBLIC;

		if (yyvsp[-1].itemptr->i_string[0] != '.')
			llseq++;

		switch(yyvsp[-1].itemptr->i_token) {
		case UNDECLARED:
			if (pass2) {
				sprintf(detail, "%s error - label '%s' not declared",
					errname[pflag], yyvsp[-1].itemptr->i_string);
				errwarn(pflag, detail);
			}
			else {
				yyvsp[-1].itemptr->i_token = LABEL;
				yyvsp[-1].itemptr->i_pass = npass;
				yyvsp[-1].itemptr->i_value = dollarsign;
			}
			break;
		case LABEL:
			if (!pass2) {
				yyvsp[-1].itemptr->i_token = MULTDEF;
				yyvsp[-1].itemptr->i_pass = npass;
				err[mflag]++;
			} else if (yyvsp[-1].itemptr->i_value != dollarsign) {
				// XXX - perhaps only allow retrys if JR promotions are in play?
				if (outpass) {
					if (!passfail) {
						sprintf(detail, "%s error - label '%s' changed from $%04x to $%04x",
							errname[pflag], yyvsp[-1].itemptr->i_string, yyvsp[-1].itemptr->i_value, dollarsign);
						errwarn(pflag, detail);
					}
				}
				else {
					yyvsp[-1].itemptr->i_value = dollarsign;
					passretry = 1;
				}
			}
			break;
		default:
			err[mflag]++;
			yyvsp[-1].itemptr->i_token = MULTDEF;
			yyvsp[-1].itemptr->i_pass = npass;
		}
	;
    break;}
case 69:
#line 3010 "zmac.y"
{
		if (!(yyvsp[0].itemptr->i_scope & SCOPE_COMBLOCK))
			yyvsp[0].itemptr->i_scope |= SCOPE_PUBLIC;
		// Just being "public" does not #ifdef define a symbol.
		if (pass2) {
			if (yyvsp[0].itemptr->i_token == UNDECLARED) {
				sprintf(detail, "'%s' %s", yyvsp[0].itemptr->i_string, errname[uflag]);
				errwarn(uflag, detail);
			}
		}
	;
    break;}
case 72:
#line 3030 "zmac.y"
{
		if (pass2 && yyvsp[0].itemptr->i_scope != SCOPE_NONE && !(yyvsp[0].itemptr->i_scope & SCOPE_EXTERNAL)) {
			fprintf(stderr, "Label scope change\n");
			err[fflag]++;
		}
		yyvsp[0].itemptr->i_pass = npass; // external labels seen as defined for #ifdef
		yyvsp[0].itemptr->i_scope |= SCOPE_EXTERNAL;
		if (pass2) {
			if (yyvsp[0].itemptr->i_token != UNDECLARED) {
				fprintf(stderr, "External label defined locally.\n");
				err[fflag]++;
			}
		}
	;
    break;}
case 73:
#line 3047 "zmac.y"
{ yyval.ival = '+'; ;
    break;}
case 74:
#line 3048 "zmac.y"
{ yyval.ival = '-'; ;
    break;}
case 75:
#line 3049 "zmac.y"
{ yyval.ival = '*'; ;
    break;}
case 76:
#line 3050 "zmac.y"
{ yyval.ival = '/'; ;
    break;}
case 77:
#line 3051 "zmac.y"
{ yyval.ival = '%'; ;
    break;}
case 78:
#line 3052 "zmac.y"
{ yyval.ival = '&'; ;
    break;}
case 79:
#line 3053 "zmac.y"
{ yyval.ival = '|'; ;
    break;}
case 80:
#line 3054 "zmac.y"
{ yyval.ival = '^'; ;
    break;}
case 81:
#line 3055 "zmac.y"
{ yyval.ival = ANDAND; ;
    break;}
case 82:
#line 3056 "zmac.y"
{ yyval.ival = OROR; ;
    break;}
case 83:
#line 3057 "zmac.y"
{ yyval.ival = SHL; ;
    break;}
case 84:
#line 3058 "zmac.y"
{ yyval.ival = SHR; ;
    break;}
case 85:
#line 3060 "zmac.y"
{ yyval.ival = '+'; ;
    break;}
case 86:
#line 3061 "zmac.y"
{ yyval.ival = '-'; ;
    break;}
case 87:
#line 3062 "zmac.y"
{ yyval.ival = '*'; ;
    break;}
case 88:
#line 3063 "zmac.y"
{ yyval.ival = '/'; ;
    break;}
case 89:
#line 3064 "zmac.y"
{ yyval.ival = '%'; ;
    break;}
case 90:
#line 3065 "zmac.y"
{ yyval.ival = '&'; ;
    break;}
case 91:
#line 3066 "zmac.y"
{ yyval.ival = '|'; ;
    break;}
case 92:
#line 3067 "zmac.y"
{ yyval.ival = '^'; ;
    break;}
case 93:
#line 3068 "zmac.y"
{ yyval.ival = MROP_SHL; ;
    break;}
case 94:
#line 3069 "zmac.y"
{ yyval.ival = MROP_SHR; ;
    break;}
case 95:
#line 3070 "zmac.y"
{ yyval.ival = MROP_SHIFT; ;
    break;}
case 96:
#line 3075 "zmac.y"
{ emit1(yyvsp[0].itemptr->i_value, 0, 0, ET_NOARG); ;
    break;}
case 97:
#line 3078 "zmac.y"
{
			// XXX - maybe splitting out CPI is better?
			if (!z80 && yyvsp[-1].itemptr->i_value == 0166641)
				emit1(0376, 0, yyvsp[0].exprptr, ET_BYTE);
			else
				err[fflag]++;
		;
    break;}
case 98:
#line 3087 "zmac.y"
{
			if (!z80 && (yyvsp[0].itemptr->i_value & 070) < 020)
				emit(1, E_CODE, 0, 007 | (yyvsp[0].itemptr->i_value & 070));
			else
				err[fflag]++;
		;
    break;}
case 99:
#line 3095 "zmac.y"
{
		if (yyvsp[0].exprptr->e_parenthesized)
			errwarn(warn_general, "JP (addr) is equivalent to JP addr");

		if (z80 || yyvsp[-1].itemptr->i_value == 0303) {
			checkjp(0, yyvsp[0].exprptr);
			emit(1, E_CODE16, yyvsp[0].exprptr, 0303);
		}
		else
			// can't optimize jump on plus
			emit(1, E_CODE16, yyvsp[0].exprptr, 0362);
	;
    break;}
case 100:
#line 3109 "zmac.y"
{	emit(1, E_CODE16, yyvsp[0].exprptr, 0315);	;
    break;}
case 101:
#line 3112 "zmac.y"
{
		// accepts rst 0-7 or rst 0,8,16,...,56
		int vec = yyvsp[0].exprptr->e_value;
		expr_number_check(yyvsp[0].exprptr);
		if ((vec > 7 || vec < 0) && (vec & ~(7 << 3)))
			err[vflag]++;
		if (vec > 7) vec >>= 3;
		emit(1, E_CODE, 0, yyvsp[-1].itemptr->i_value + ((vec & 7) << 3));
		expr_free(yyvsp[0].exprptr);
	;
    break;}
case 102:
#line 3124 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value, 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 103:
#line 3127 "zmac.y"
{
			emit(3, E_CODE, 0, yyvsp[-1].itemptr->i_value >> 8, yyvsp[-1].itemptr->i_value, disp);
		;
    break;}
case 104:
#line 3132 "zmac.y"
{ emit1(0306, 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 105:
#line 3135 "zmac.y"
{ emit1(0306, 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 106:
#line 3138 "zmac.y"
{ emit1(0306 + (yyvsp[-1].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 107:
#line 3141 "zmac.y"
{ emit1(0306 + (yyvsp[-3].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 108:
#line 3144 "zmac.y"
{
			// CP is CALL P in 8080
			if (!z80 && yyvsp[-1].itemptr->i_value == 0270 && yyvsp[-1].itemptr->i_string[1] == 'p')
				emit(1, E_CODE16, yyvsp[0].exprptr, 0364);
			else
				emit1(0306 | (yyvsp[-1].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE);
		;
    break;}
case 109:
#line 3153 "zmac.y"
{ emit1(0306 | (yyvsp[-1].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 110:
#line 3156 "zmac.y"
{ emit1(0306 | (yyvsp[-1].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 111:
#line 3159 "zmac.y"
{ emit1(0306 | (yyvsp[-1].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 112:
#line 3162 "zmac.y"
{ emit(2, E_CODE8, yyvsp[0].exprptr, 0xED, 0x60 | yyvsp[-1].itemptr->i_value); ;
    break;}
case 113:
#line 3165 "zmac.y"
{ emit1(0306 | (yyvsp[-3].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 114:
#line 3168 "zmac.y"
{ emit1(0306 | (yyvsp[-3].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 115:
#line 3171 "zmac.y"
{ emit1(0306 | (yyvsp[-3].itemptr->i_value & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 116:
#line 3174 "zmac.y"
{ emit1(0306 | (yyvsp[-3].itemptr->i_value  & 070), 0, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 117:
#line 3177 "zmac.y"
{ emit1(0200 + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 118:
#line 3180 "zmac.y"
{ emit1(0200 + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 119:
#line 3183 "zmac.y"
{ emit(1, E_CODE, 0, 0206); ;
    break;}
case 120:
#line 3186 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 121:
#line 3189 "zmac.y"
{ emit1(yyvsp[-3].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 122:
#line 3192 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 123:
#line 3195 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 124:
#line 3198 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 125:
#line 3201 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 126:
#line 3204 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 127:
#line 3207 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 128:
#line 3210 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival << 3), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 129:
#line 3213 "zmac.y"
{ emit1(yyvsp[-3].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 130:
#line 3216 "zmac.y"
{ emit1(yyvsp[-3].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 131:
#line 3219 "zmac.y"
{ emit1(yyvsp[-3].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 132:
#line 3222 "zmac.y"
{ emit1(yyvsp[-3].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 133:
#line 3225 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 134:
#line 3228 "zmac.y"
{
			emit(4, E_CODE, 0, yyvsp[-1].itemptr->i_value >> 24, yyvsp[-1].itemptr->i_value >> 16, disp, yyvsp[-1].itemptr->i_value);
		;
    break;}
case 135:
#line 3233 "zmac.y"
{ emit1(yyvsp[-3].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[-2].ival, 0, ET_NOARG_DISP); ;
    break;}
case 136:
#line 3236 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + ((yyvsp[0].ival & 0377) << 3), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 137:
#line 3239 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + ((yyvsp[0].ival & 0377) << 3), yyvsp[0].ival, 0, ET_NOARG_DISP); ;
    break;}
case 138:
#line 3242 "zmac.y"
{ if (yyvsp[-3].itemptr->i_value == 0210)
				emit(2,E_CODE,0,0355,0112+yyvsp[0].ival);
			else
				emit(2,E_CODE,0,0355,0102+yyvsp[0].ival);
		;
    break;}
case 139:
#line 3249 "zmac.y"
{ emitdad(yyvsp[-2].ival,yyvsp[0].ival); ;
    break;}
case 140:
#line 3252 "zmac.y"
{
			if (yyvsp[-2].ival != yyvsp[0].ival) {
				fprintf(stderr,"ADD mar, mar error\n");
				err[gflag]++;
			}
			emitdad(yyvsp[-2].ival,yyvsp[0].ival);
		;
    break;}
case 141:
#line 3260 "zmac.y"
{ emitdad(040, yyvsp[0].ival); ;
    break;}
case 142:
#line 3263 "zmac.y"
{
			emit(2, E_CODE, 0, yyvsp[-1].itemptr->i_value >> 8, yyvsp[-1].itemptr->i_value | yyvsp[0].ival);
		;
    break;}
case 143:
#line 3268 "zmac.y"
{
			int dst = yyvsp[-1].itemptr->i_value >> 8;
			int reg = yyvsp[0].ival >> 8;
			if (!reg) reg = 0xed;

			if (dst != reg) {
				if (dst == 0xed)
					fprintf(stderr, "dadc/dsbc cannot take ix or iy\n");
				else if (dst == 0xdd)
					fprintf(stderr, "dadx cannot take hl or iy\n");
				else
					fprintf(stderr, "dady cannot take hl or ix\n");
				err[gflag]++;
			}
			emit(2, E_CODE, 0, yyvsp[-1].itemptr->i_value >> 8, yyvsp[-1].itemptr->i_value | yyvsp[0].ival);
		;
    break;}
case 144:
#line 3286 "zmac.y"
{ emit1(((yyvsp[-1].itemptr->i_value & 1) << 3) + (yyvsp[0].ival & 0377) + 3, yyvsp[0].ival, 0, ET_NOARG); ;
    break;}
case 145:
#line 3289 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG); ;
    break;}
case 146:
#line 3292 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG); ;
    break;}
case 147:
#line 3295 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG); ;
    break;}
case 148:
#line 3298 "zmac.y"
{ emit1(yyvsp[-1].itemptr->i_value + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG); ;
    break;}
case 149:
#line 3301 "zmac.y"
{
			if (strcmp(yyvsp[-1].itemptr->i_string, "set") == 0 && label) {
				// Clear error that label definition will have been set
				err[mflag] = 0;
				itemcpy(label, &pristine_label);
				do_defl(label, yyvsp[0].exprptr, 0);
				list_dollarsign = 0;
				list_addr = label->i_value;
			}
			else {
				err[fflag]++;
			}
		;
    break;}
case 150:
#line 3316 "zmac.y"
{
			int bit = yyvsp[-2].exprptr->e_value;
			expr_number_check(yyvsp[-2].exprptr);
			expr_free(yyvsp[-2].exprptr);
			if (bit < 0 || bit > 7)
				err[vflag]++;
			emit1(yyvsp[-3].itemptr->i_value + ((bit & 7) << 3) + (yyvsp[0].ival & 0377), yyvsp[0].ival, 0, ET_NOARG_DISP);
		;
    break;}
case 151:
#line 3326 "zmac.y"
{
			int bit = yyvsp[-2].exprptr->e_value;
			expr_number_check(yyvsp[-2].exprptr);
			expr_free(yyvsp[-2].exprptr);
			if (bit < 0 || bit > 7)
				err[vflag]++;
			emit(4, E_CODE, 0, yyvsp[-3].itemptr->i_value >> 24, yyvsp[-3].itemptr->i_value >> 16, disp,
				yyvsp[-3].itemptr->i_value | (bit << 3));
		;
    break;}
case 152:
#line 3337 "zmac.y"
{
			int bit = yyvsp[-4].exprptr->e_value;
			expr_number_check(yyvsp[-4].exprptr);
			expr_free(yyvsp[-4].exprptr);
			if (bit < 0 || bit > 7)
				err[vflag]++;
			emit1(yyvsp[-5].itemptr->i_value + ((bit & 7) << 3) + (yyvsp[0].ival & 0377), yyvsp[-2].ival, 0, ET_NOARG_DISP);
		;
    break;}
case 153:
#line 3347 "zmac.y"
{
		checkjp(yyvsp[-2].ival, yyvsp[0].exprptr);
		emit(1, E_CODE16, yyvsp[0].exprptr, 0302 + yyvsp[-2].ival);
	;
    break;}
case 154:
#line 3353 "zmac.y"
{
		checkjp(yyvsp[-1].itemptr->i_value, yyvsp[0].exprptr);
		emit(1, E_CODE16, yyvsp[0].exprptr, yyvsp[-1].itemptr->i_value);
	;
    break;}
case 155:
#line 3359 "zmac.y"
{ emit1(0351, yyvsp[-1].ival, 0, ET_NOARG); ;
    break;}
case 156:
#line 3362 "zmac.y"
{ emit1(0351, yyvsp[0].ival, 0, ET_NOARG); ;
    break;}
case 157:
#line 3365 "zmac.y"
{ emit(1, E_CODE16, yyvsp[0].exprptr, 0304 + yyvsp[-2].ival); ;
    break;}
case 158:
#line 3368 "zmac.y"
{ emit(1, E_CODE16, yyvsp[0].exprptr, yyvsp[-1].itemptr->i_value); ;
    break;}
case 159:
#line 3371 "zmac.y"
{ emitjr(030,yyvsp[0].exprptr); ;
    break;}
case 160:
#line 3374 "zmac.y"
{ emitjr(yyvsp[-3].itemptr->i_value + yyvsp[-2].ival, yyvsp[0].exprptr); ;
    break;}
case 161:
#line 3377 "zmac.y"
{ emitjr(yyvsp[-1].itemptr->i_value, yyvsp[0].exprptr); ;
    break;}
case 162:
#line 3380 "zmac.y"
{ emitjr(yyvsp[-1].itemptr->i_value, yyvsp[0].exprptr); ;
    break;}
case 163:
#line 3383 "zmac.y"
{ emit(1, E_CODE, 0, yyvsp[0].itemptr->i_value); ;
    break;}
case 164:
#line 3386 "zmac.y"
{ emit(1, E_CODE, 0, 0300 + yyvsp[0].ival); ;
    break;}
case 165:
#line 3389 "zmac.y"
{
			// Many constraints on byte access to IX/IY registers.
			if ((yyvsp[-2].ival | yyvsp[0].ival) >> 16) {
				int a = yyvsp[-2].ival;
				int b = yyvsp[0].ival;

				// Only ixh,ixh; ixh,ixl; ixl,ixh; ixl,ixl allowed.
				if (a >> 16 && b >> 16) {
					if (a >> 8 != b >> 8) {
						fprintf(stderr, "LD cannot move between ix and iy\n");
						err[gflag]++;
					}
				}
				else {
					int c = b >> 16 ? a : b;
					// No access to h, l, (hl), (ix), (iy)
					if (c == 4 || c == 5 || (c & 0xff) == 6) {
						fprintf(stderr, "LD cannot combine i/xy/lh and h,l,(hl),(ix) or (iy).\n");
						err[gflag]++;
					}
				}
			}

			if ((yyvsp[-2].ival & 0377) == 6 && (yyvsp[0].ival & 0377) == 6) {
				fprintf(stderr,"LD reg, reg error: can't do memory to memory\n");
				err[gflag]++;
			}
			emit1(0100 + ((yyvsp[-2].ival & 7) << 3) + (yyvsp[0].ival & 7), yyvsp[-2].ival | yyvsp[0].ival, 0, ET_NOARG_DISP);
		;
    break;}
case 166:
#line 3420 "zmac.y"
{
			emit(3, E_CODE, 0, yyvsp[-3].itemptr->i_value >> 8, yyvsp[-3].itemptr->i_value | (yyvsp[-2].ival << 3), disp);
		;
    break;}
case 167:
#line 3425 "zmac.y"
{
			emit(3, E_CODE, 0, yyvsp[-3].itemptr->i_value >> 8, yyvsp[-3].itemptr->i_value | yyvsp[-2].ival, disp);
		;
    break;}
case 168:
#line 3430 "zmac.y"
{
			if (yyvsp[-2].ival == 6 && yyvsp[0].ival == 6) err[gflag]++;
			emit1(0100 + ((yyvsp[-2].ival & 7) << 3) + (yyvsp[0].ival & 7),yyvsp[-2].ival | yyvsp[0].ival, 0, ET_NOARG_DISP);
		;
    break;}
case 169:
#line 3436 "zmac.y"
{ emit1(6 + ((yyvsp[-2].ival & 0377) << 3), yyvsp[-2].ival, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 170:
#line 3439 "zmac.y"
{
			emit(3, E_CODE8, yyvsp[-2].exprptr, yyvsp[-3].itemptr->i_value >> 8, yyvsp[-3].itemptr->i_value, disp);
		;
    break;}
case 171:
#line 3444 "zmac.y"
{ emit1(6 + ((yyvsp[-2].ival & 0377) << 3), yyvsp[-2].ival, yyvsp[0].exprptr, ET_BYTE); ;
    break;}
case 172:
#line 3447 "zmac.y"
{	if (yyvsp[-4].ival != 7) {
				fprintf(stderr,"LD reg, (RP) error\n");
				err[gflag]++;
			}
			else emit(1, E_CODE, 0, 012 + yyvsp[-1].itemptr->i_value);
		;
    break;}
case 173:
#line 3455 "zmac.y"
{
			if (yyvsp[0].ival != 0 && yyvsp[0].ival != 2) err[gflag]++;
			emit(1, E_CODE, 0, 012 + (yyvsp[0].ival << 3));
		;
    break;}
case 174:
#line 3461 "zmac.y"
{
			if (yyvsp[-2].ival != 7) {
				fprintf(stderr,"LD reg, (expr) error: A only valid destination\n");
				err[gflag]++;
			}
			else {
				expr_word_check(yyvsp[0].exprptr);
				emit(1, E_CODE16, yyvsp[0].exprptr, 072);
			}
		;
    break;}
case 175:
#line 3473 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			emit(1, E_CODE16, yyvsp[0].exprptr, 072);
		;
    break;}
case 176:
#line 3479 "zmac.y"
{ emit(1, E_CODE, 0, 2 + yyvsp[-3].itemptr->i_value); ;
    break;}
case 177:
#line 3482 "zmac.y"
{
			if (yyvsp[0].ival != 0 && yyvsp[0].ival != 2) err[gflag]++;
			emit(1, E_CODE, 0, 2 + (yyvsp[0].ival << 3));
		;
    break;}
case 178:
#line 3488 "zmac.y"
{
			expr_word_check(yyvsp[-2].exprptr);
			emit(1, E_CODE16, yyvsp[-2].exprptr, 062);
		;
    break;}
case 179:
#line 3494 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			emit(1, E_CODE16, yyvsp[0].exprptr, 062);
		;
    break;}
case 180:
#line 3500 "zmac.y"
{
			if (yyvsp[-2].ival != 7) {
				fprintf(stderr,"LD reg, MISCREG error: A only valid destination\n");
				err[gflag]++;
			}
			else emit(2, E_CODE, 0, 0355, 0127 + yyvsp[0].itemptr->i_value);
		;
    break;}
case 181:
#line 3509 "zmac.y"
{ emit(2, E_CODE, 0, 0355, 0107 + yyvsp[-2].itemptr->i_value); ;
    break;}
case 182:
#line 3512 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			emit1(1 + (yyvsp[-2].ival & 060), yyvsp[-2].ival, yyvsp[0].exprptr, ET_WORD);
		;
    break;}
case 183:
#line 3518 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			emit1(1 + (yyvsp[-2].ival & 060), yyvsp[-2].ival, yyvsp[0].exprptr, ET_WORD);
		;
    break;}
case 184:
#line 3524 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			if ((yyvsp[-2].ival & 060) == 040)
				emit1(052, yyvsp[-2].ival, yyvsp[0].exprptr, ET_WORD);
			else
				emit(2, E_CODE16, yyvsp[0].exprptr, 0355, 0113 + yyvsp[-2].ival);
		;
    break;}
case 185:
#line 3533 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			emit1(052, 040, yyvsp[0].exprptr, ET_WORD);
		;
    break;}
case 186:
#line 3539 "zmac.y"
{
			expr_word_check(yyvsp[-2].exprptr);
			if ((yyvsp[0].ival & 060) == 040)
				emit1(042, yyvsp[0].ival, yyvsp[-2].exprptr, ET_WORD);
			else
				emit(2, E_CODE16, yyvsp[-2].exprptr, 0355, 0103 + yyvsp[0].ival);
		;
    break;}
case 187:
#line 3548 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			emit1(042, 040, yyvsp[0].exprptr, ET_WORD);
		;
    break;}
case 188:
#line 3554 "zmac.y"
{
			if (yyvsp[-2].ival != 060) {
				fprintf(stderr,"LD evenreg error\n");
				err[gflag]++;
			}
			else
				emit1(0371, yyvsp[0].ival, 0, ET_NOARG);
		;
    break;}
case 189:
#line 3564 "zmac.y"
{
			expr_word_check(yyvsp[0].exprptr);
			emit(2, E_CODE16, yyvsp[0].exprptr, yyvsp[-1].itemptr->i_value >> 8, yyvsp[-1].itemptr->i_value);
		;
    break;}
case 190:
#line 3570 "zmac.y"
{
			if (yyvsp[-2].itemptr->i_value != 020) {
				fprintf(stderr,"EX RP, HL error\n");
				err[gflag]++;
			}
			else
				emit(1, E_CODE, 0, 0353);
		;
    break;}
case 191:
#line 3580 "zmac.y"
{ emit(1, E_CODE, 0, 010); ;
    break;}
case 192:
#line 3583 "zmac.y"
{ emit1(0343, yyvsp[0].ival, 0, ET_NOARG); ;
    break;}
case 193:
#line 3586 "zmac.y"
{
			if (yyvsp[-2].ival != 7) {
				fprintf(stderr,"IN reg, (expr) error\n");
				err[gflag]++;
			}
			else	{
				if (yyvsp[0].exprptr->e_value < 0 || yyvsp[0].exprptr->e_value > 255)
					err[vflag]++;
				emit(1, E_CODE8, yyvsp[0].exprptr, yyvsp[-3].itemptr->i_value);
			}
		;
    break;}
case 194:
#line 3599 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < 0 || yyvsp[0].exprptr->e_value > 255)
				err[vflag]++;
			emit(2, E_CODE8, yyvsp[0].exprptr, yyvsp[-3].itemptr->i_value >> 8,
				yyvsp[-3].itemptr->i_value | (yyvsp[-2].ival << 3));
		;
    break;}
case 195:
#line 3607 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < 0 || yyvsp[0].exprptr->e_value > 255)
				err[vflag]++;
			emit(2, E_CODE8, yyvsp[0].exprptr, yyvsp[-1].itemptr->i_value >> 8,
				yyvsp[-1].itemptr->i_value | (6 << 3));
		;
    break;}
case 196:
#line 3615 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < 0 || yyvsp[0].exprptr->e_value > 255)
				err[vflag]++;
			emit(1, E_CODE8, yyvsp[0].exprptr, yyvsp[-1].itemptr->i_value);
		;
    break;}
case 197:
#line 3622 "zmac.y"
{ emit(2, E_CODE, 0, 0355, 0100 + (yyvsp[-4].ival << 3)); ;
    break;}
case 198:
#line 3625 "zmac.y"
{ emit(2, E_CODE, 0, 0355, 0100 + (yyvsp[0].ival << 3)); ;
    break;}
case 199:
#line 3628 "zmac.y"
{ emit(2, E_CODE, 0, 0355, 0160); ;
    break;}
case 200:
#line 3631 "zmac.y"
{ emit(2, E_CODE, 0, 0355, 0160); ;
    break;}
case 201:
#line 3634 "zmac.y"
{
			if (yyvsp[-2].exprptr->e_value < 0 || yyvsp[-2].exprptr->e_value > 255)
				err[vflag]++;
			emit(1, E_CODE8, yyvsp[-2].exprptr, yyvsp[-3].itemptr->i_value);
		;
    break;}
case 202:
#line 3641 "zmac.y"
{
			if (yyvsp[-2].exprptr->e_value < 0 || yyvsp[-2].exprptr->e_value > 255)
				err[vflag]++;
			emit(2, E_CODE8, yyvsp[-2].exprptr, yyvsp[-3].itemptr->i_value >> 8,
				yyvsp[-3].itemptr->i_value | (yyvsp[0].ival << 3));
		;
    break;}
case 203:
#line 3649 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < 0 || yyvsp[0].exprptr->e_value > 255)
				err[vflag]++;
			emit(1, E_CODE8, yyvsp[0].exprptr, yyvsp[-1].itemptr->i_value);
		;
    break;}
case 204:
#line 3656 "zmac.y"
{ emit(2, E_CODE, 0, 0355, 0101 + (yyvsp[0].ival << 3)); ;
    break;}
case 205:
#line 3659 "zmac.y"
{ emit(2, E_CODE, 0, 0355, 0101 + (yyvsp[0].ival << 3)); ;
    break;}
case 206:
#line 3662 "zmac.y"
{
			expr_number_check(yyvsp[0].exprptr);
			if (yyvsp[0].exprptr->e_value != 0) {
				fprintf(stderr, "Can only output 0 to port C with OUT\n");
				err[vflag]++;
			}
			expr_free(yyvsp[0].exprptr);

			emit(2, E_CODE, 0, 0355, 0101 + (6 << 3));
		;
    break;}
case 207:
#line 3674 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < 0 || yyvsp[0].exprptr->e_value > 255)
				err[vflag]++;

			emit(2, E_CODE8, yyvsp[0].exprptr, yyvsp[-1].itemptr->i_value >> 8, yyvsp[-1].itemptr->i_value);
		;
    break;}
case 208:
#line 3682 "zmac.y"
{
			int im = yyvsp[0].exprptr->e_value;
			expr_number_check(yyvsp[0].exprptr);
			expr_free(yyvsp[0].exprptr);
			if (im > 2 || im < 0)
				err[vflag]++;
			else
				emit(2, E_CODE, 0, yyvsp[-1].itemptr->i_value >> 8, yyvsp[-1].itemptr->i_value + ((im + (im > 0)) << 3));
		;
    break;}
case 209:
#line 3693 "zmac.y"
{
			expr_number_check(yyvsp[0].exprptr);
			if (phaseflag) {
				err[oflag]++;
			} else {
				phaseflag = 1;
				phdollar = dollarsign;
				dollarsign = yyvsp[0].exprptr->e_value;
				phbegin = dollarsign;
			}
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 210:
#line 3707 "zmac.y"
{
			if (!phaseflag) {
				err[oflag]++;
			} else {
				phaseflag = 0;
				dollarsign = phdollar + dollarsign - phbegin;
			}
		;
    break;}
case 211:
#line 3717 "zmac.y"
{
			expr_reloc_check(yyvsp[0].exprptr);
			// Cannot org to the other segment (but absolute values are OK)
			if (relopt && segment &&
				(yyvsp[0].exprptr->e_scope & SCOPE_SEGMASK) &&
				(yyvsp[0].exprptr->e_scope & SCOPE_SEGMASK) != segment)
			{
				err[rflag]++;
			}
			if (phaseflag) {
				err[oflag]++;
				dollarsign = phdollar + dollarsign - phbegin;
				phaseflag = 0;
			}
			if (yyvsp[0].exprptr->e_value-dollarsign) {
				flushbin();
				flushoth();
				olddollar = yyvsp[0].exprptr->e_value;
				oldothdollar = yyvsp[0].exprptr->e_value;
				dollarsign = yyvsp[0].exprptr->e_value;
				emit_addr = yyvsp[0].exprptr->e_value;
				seg_pos[segment] = dollarsign;
				if (seg_pos[segment] > seg_size[segment]) {
					seg_size[segment] = seg_pos[segment];
					if (segment == SEG_COMMON && cur_common)
						cur_common->i_value = seg_size[segment];
				}
				putrelcmd(RELCMD_SETLOC);
				putrelsegref(segment, seg_pos[segment]);
				segchange = 0;
			}
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 212:
#line 3752 "zmac.y"
{
			list_dollarsign = 0;
			list_addr = yyvsp[0].exprptr->e_value;
			expr_number_check(yyvsp[0].exprptr);
			if (outpass && !yyvsp[0].exprptr->e_value)
			{
				err[aflag]++;
			}
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 213:
#line 3764 "zmac.y"
{
			list_dollarsign = 0;
			list_addr = yyvsp[0].exprptr->e_value;
			expr_number_check(yyvsp[0].exprptr);
			tstates = yyvsp[0].exprptr->e_value;
			tstatesum[emit_addr] = tstates;
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 214:
#line 3774 "zmac.y"
{
			list_dollarsign = 0;
			list_addr = yyvsp[0].exprptr->e_value;
			expr_number_check(yyvsp[0].exprptr);
			ocf = yyvsp[0].exprptr->e_value;
			ocfsum[emit_addr] = ocf;
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 215:
#line 3783 "zmac.y"
{ full_exprs = 1; ;
    break;}
case 216:
#line 3783 "zmac.y"
{ full_exprs = 0; ;
    break;}
case 217:
#line 3785 "zmac.y"
{ full_exprs = 1; ;
    break;}
case 218:
#line 3785 "zmac.y"
{ full_exprs = 0; ;
    break;}
case 219:
#line 3787 "zmac.y"
{ full_exprs = 1; ;
    break;}
case 220:
#line 3787 "zmac.y"
{ full_exprs = 0; ;
    break;}
case 221:
#line 3789 "zmac.y"
{ full_exprs = 1; ;
    break;}
case 222:
#line 3789 "zmac.y"
{ full_exprs = 0; ;
    break;}
case 227:
#line 3801 "zmac.y"
{ param_parse = 1; ;
    break;}
case 228:
#line 3801 "zmac.y"
{ param_parse = 0; ;
    break;}
case 229:
#line 3803 "zmac.y"
{ yyval.ival = 0; ;
    break;}
case 230:
#line 3803 "zmac.y"
{ yyval.ival = 1; ;
    break;}
case 231:
#line 3807 "zmac.y"
{
			if (parm_number >= PARMMAX)
				error("Too many parameters");
			yyvsp[0].itemptr->i_value = parm_number++;
			yyvsp[0].itemptr->i_scope = yyvsp[-1].ival;
			yyvsp[0].itemptr->i_chain = 0;
		;
    break;}
case 232:
#line 3816 "zmac.y"
{
		static char macpush[LINEBUFFERSIZE];
		// Because of locals the parser has to look ahead.
		// We'll have buffered that as we usually do so just a
		// matter of picking that up and cancelling any look-ahead.
		*lineptr = '\0';
		strcpy(macpush, linebuf);
		lineptr = linebuf;
		peekc = NOPEEK;
		yychar = YYEMPTY;
		yyval.cval = macpush;
	;
    break;}
case 234:
#line 3832 "zmac.y"
{ param_parse = 1; ;
    break;}
case 235:
#line 3832 "zmac.y"
{ param_parse = 0; list1(); ;
    break;}
case 239:
#line 3844 "zmac.y"
{
			if (parm_number >= PARMMAX)
				error("Too many parameters");
			yyvsp[0].itemptr->i_value = parm_number++;
			yyvsp[0].itemptr->i_scope = 0;
			yyvsp[0].itemptr->i_chain = 1;
		;
    break;}
case 243:
#line 3864 "zmac.y"
{
			cp = malloc(strlen(tempbuf)+1);
#ifdef M_DEBUG
			fprintf (stderr, "[Arg%u(%p): %s]\n", parm_number, cp, tempbuf);
#endif
			est2[parm_number++].param = cp;
			strcpy(cp, tempbuf);
		;
    break;}
case 244:
#line 3873 "zmac.y"
{ arg_flag = 0; ;
    break;}
case 245:
#line 3874 "zmac.y"
{
			arg_flag = 1;
			expr_reloc_check(yyvsp[0].exprptr);
			sprintf(tempbuf, "%d", yyvsp[0].exprptr->e_value);
			est2[parm_number++].param = strdup(tempbuf);
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 250:
#line 3895 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 253:
#line 3905 "zmac.y"
{ if (yyvsp[0].itemptr->i_value != 070) err[gflag]++; yyval.ival = 6; ;
    break;}
case 254:
#line 3909 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 255:
#line 3914 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 256:
#line 3919 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 257:
#line 3925 "zmac.y"
{
			yyval.ival = 6;
		;
    break;}
case 259:
#line 3933 "zmac.y"
{
			yyval.ival = (yyvsp[-2].itemptr->i_value & 0177400) | 6;
		;
    break;}
case 260:
#line 3938 "zmac.y"
{
			disp = 0;
			yyval.ival = (yyvsp[-1].itemptr->i_value & 0177400) | 6;
		;
    break;}
case 261:
#line 3944 "zmac.y"
{
			yyval.ival = (yyvsp[-1].itemptr->i_value & 0177400) | 6;
		;
    break;}
case 262:
#line 3949 "zmac.y"
{
			expr_number_check(yyvsp[0].exprptr);
			disp = yyvsp[0].exprptr->e_value;
			expr_free(yyvsp[0].exprptr);
			if (disp > 127 || disp < -128)
				err[vflag]++;
		;
    break;}
case 265:
#line 3963 "zmac.y"
{ if (yyvsp[0].ival & 1) err[gflag]++; yyval.ival = yyvsp[0].ival << 3; ;
    break;}
case 266:
#line 3965 "zmac.y"
{ yyval.ival = yyvsp[0].itemptr->i_value; ;
    break;}
case 267:
#line 3969 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 268:
#line 3974 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 269:
#line 3979 "zmac.y"
{
			yyval.ival = 060;
		;
    break;}
case 271:
#line 3986 "zmac.y"
{ if ((yyvsp[0].ival & 1) && yyvsp[0].ival != 7) err[gflag]++; yyval.ival = (yyvsp[0].ival & 6) << 3; ;
    break;}
case 272:
#line 3988 "zmac.y"
{ yyval.ival = yyvsp[0].itemptr->i_value; ;
    break;}
case 273:
#line 3992 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 274:
#line 3997 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 276:
#line 4005 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 277:
#line 4011 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 278:
#line 4016 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 279:
#line 4022 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 280:
#line 4027 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 292:
#line 4037 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 293:
#line 4043 "zmac.y"
{
			yyval.ival = yyvsp[0].itemptr->i_value;
		;
    break;}
case 294:
#line 4048 "zmac.y"
{	yyval.ival = 030;	;
    break;}
case 297:
#line 4057 "zmac.y"
{
			cp = yyvsp[0].cval;
			while (*cp != '\0')
				emit(1,E_DATA,expr_num(*cp++));
		;
    break;}
case 298:
#line 4064 "zmac.y"
{
			// Allow a single "TWOCHAR" value...
			if (yyvsp[0].exprptr->e_scope & SCOPE_TWOCHAR) {
				emit(1, E_DATA, expr_num(yyvsp[0].exprptr->e_value & 0xff));
				emit(1, E_DATA, expr_num(yyvsp[0].exprptr->e_value >> 8));
			}
			else {
				if (is_number(yyvsp[0].exprptr) && (yyvsp[0].exprptr->e_value < -128 || yyvsp[0].exprptr->e_value > 255)) {
					err[vflag]++;
				}

				emit(1, E_DATA, yyvsp[0].exprptr);
			}
		;
    break;}
case 301:
#line 4090 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < -32768 || yyvsp[0].exprptr->e_value > 65535) {
				err[vflag]++;
			}
			emit(2, E_DATA, yyvsp[0].exprptr);
		;
    break;}
case 304:
#line 4107 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < -0x800000 || yyvsp[0].exprptr->e_value > 0xffffff) {
				err[vflag]++;
			}
			emit(3, E_DATA, yyvsp[0].exprptr);
		;
    break;}
case 307:
#line 4124 "zmac.y"
{
			// Can't check overflow as I only have 32 bit ints.
			emit(4, E_DATA, yyvsp[0].exprptr);
		;
    break;}
case 310:
#line 4138 "zmac.y"
{	yyval.exprptr = yyvsp[-1].exprptr; yyval.exprptr->e_parenthesized = 1;	;
    break;}
case 311:
#line 4155 "zmac.y"
{
			yyval.exprptr = expr_var(yyvsp[0].itemptr);
			yyvsp[0].itemptr->i_uses++;
		;
    break;}
case 312:
#line 4161 "zmac.y"
{
			yyval.exprptr = expr_num(yyvsp[0].ival);
		;
    break;}
case 313:
#line 4166 "zmac.y"
{
			yyval.exprptr = expr_num(yyvsp[0].ival);
		;
    break;}
case 314:
#line 4171 "zmac.y"
{
			yyval.exprptr = expr_num(yyvsp[0].ival);
			// Mark as twochar for db.list hackery
			yyval.exprptr->e_scope |= SCOPE_TWOCHAR;
		;
    break;}
case 315:
#line 4178 "zmac.y"
{
			yyval.exprptr = expr_var(yyvsp[0].itemptr);
		;
    break;}
case 316:
#line 4183 "zmac.y"
{
			yyval.exprptr = expr_var(yyvsp[0].itemptr);
		;
    break;}
case 317:
#line 4188 "zmac.y"
{
			yyval.exprptr = expr_var(yyvsp[0].itemptr);
		;
    break;}
case 318:
#line 4193 "zmac.y"
{
			yyval.exprptr = expr_var(yyvsp[0].itemptr);
		;
    break;}
case 319:
#line 4198 "zmac.y"
{
			yyval.exprptr = expr_num(dollarsign + emitptr - emitbuf);
			yyval.exprptr->e_scope = phaseflag ? SEG_ABS : segment;
		;
    break;}
case 320:
#line 4204 "zmac.y"
{
			int chkext = 1;
			yyval.exprptr = expr_alloc();
			yyval.exprptr->e_token = 'u';
			yyval.exprptr->e_item = yyvsp[0].itemptr;
			yyval.exprptr->e_scope = yyvsp[0].itemptr->i_scope;
			yyval.exprptr->e_value = 0;

			if (!nmnvopt) {
				// Allow use of JMP, RET, etc. as values.
				struct item *i = keyword(yyvsp[0].itemptr->i_string);

				// But don't allow use of pseudo-ops as values.
				if (item_is_verb(i) && i->i_string[0] != '.') {
					chkext = 0;
					yyvsp[0].itemptr = i;
					yyval.exprptr->e_item = i;
					yyval.exprptr->e_value = item_value(i);
				}
			}

			if (chkext && !(yyvsp[0].itemptr->i_scope & SCOPE_EXTERNAL)) {
				sprintf(detail, "'%s' %s", yyvsp[0].itemptr->i_string, errname[uflag]);
				// Would be nice to add to list of undeclared errors
				errwarn(uflag, detail);
			}
		;
    break;}
case 321:
#line 4233 "zmac.y"
{
			yyval.exprptr = expr_alloc();
			yyval.exprptr->e_token = 'm';
			yyval.exprptr->e_item = yyvsp[0].itemptr;
			yyval.exprptr->e_scope = yyvsp[0].itemptr->i_scope;
			// Use the current value.  Harmless enough as this
			// will normally error out yet vital to allow
			// "var set var+1" to function.
			yyval.exprptr->e_value = yyvsp[0].itemptr->i_value;
		;
    break;}
case 322:
#line 4244 "zmac.y"
{ raw = 2; ;
    break;}
case 323:
#line 4245 "zmac.y"
{
			yyval.exprptr = expr_num(tempbuf[0] ? -1 : 0);
		;
    break;}
case 324:
#line 4248 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '+', yyvsp[0].exprptr); ;
    break;}
case 325:
#line 4249 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '-', yyvsp[0].exprptr); ;
    break;}
case 326:
#line 4250 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '/', yyvsp[0].exprptr); ;
    break;}
case 327:
#line 4251 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '*', yyvsp[0].exprptr); ;
    break;}
case 328:
#line 4252 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '%', yyvsp[0].exprptr); ;
    break;}
case 329:
#line 4253 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '&', yyvsp[0].exprptr); ;
    break;}
case 330:
#line 4254 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '&', yyvsp[0].exprptr); ;
    break;}
case 331:
#line 4255 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '|', yyvsp[0].exprptr); ;
    break;}
case 332:
#line 4256 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '|', yyvsp[0].exprptr); ;
    break;}
case 333:
#line 4257 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '^', yyvsp[0].exprptr); ;
    break;}
case 334:
#line 4258 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '^', yyvsp[0].exprptr); ;
    break;}
case 335:
#line 4259 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, SHL, yyvsp[0].exprptr); ;
    break;}
case 336:
#line 4260 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, SHR, yyvsp[0].exprptr); ;
    break;}
case 337:
#line 4261 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '<', yyvsp[0].exprptr); ;
    break;}
case 338:
#line 4262 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '<', yyvsp[0].exprptr); ;
    break;}
case 339:
#line 4263 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '=', yyvsp[0].exprptr); ;
    break;}
case 340:
#line 4264 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '=', yyvsp[0].exprptr); ;
    break;}
case 341:
#line 4265 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '>', yyvsp[0].exprptr); ;
    break;}
case 342:
#line 4266 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '>', yyvsp[0].exprptr); ;
    break;}
case 343:
#line 4267 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, LE, yyvsp[0].exprptr); ;
    break;}
case 344:
#line 4268 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, NE, yyvsp[0].exprptr); ;
    break;}
case 345:
#line 4269 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, GE, yyvsp[0].exprptr); ;
    break;}
case 346:
#line 4270 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, ANDAND, yyvsp[0].exprptr); ;
    break;}
case 347:
#line 4271 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, OROR, yyvsp[0].exprptr); ;
    break;}
case 348:
#line 4273 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '+', yyvsp[0].exprptr); ;
    break;}
case 349:
#line 4274 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '-', yyvsp[0].exprptr); ;
    break;}
case 350:
#line 4275 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '/', yyvsp[0].exprptr); ;
    break;}
case 351:
#line 4276 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '*', yyvsp[0].exprptr); ;
    break;}
case 352:
#line 4277 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '%', yyvsp[0].exprptr); ;
    break;}
case 353:
#line 4278 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '&', yyvsp[0].exprptr); ;
    break;}
case 354:
#line 4279 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '|', yyvsp[0].exprptr); ;
    break;}
case 355:
#line 4280 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '^', yyvsp[0].exprptr); ;
    break;}
case 356:
#line 4281 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, SHL, yyvsp[0].exprptr); ;
    break;}
case 357:
#line 4282 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, SHR, yyvsp[0].exprptr); ;
    break;}
case 358:
#line 4283 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '<', yyvsp[0].exprptr); ;
    break;}
case 359:
#line 4284 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '=', yyvsp[0].exprptr); ;
    break;}
case 360:
#line 4285 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, '>', yyvsp[0].exprptr); ;
    break;}
case 361:
#line 4286 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, LE, yyvsp[0].exprptr); ;
    break;}
case 362:
#line 4287 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, NE, yyvsp[0].exprptr); ;
    break;}
case 363:
#line 4288 "zmac.y"
{ yyval.exprptr = expr_mk(yyvsp[-2].exprptr, GE, yyvsp[0].exprptr); ;
    break;}
case 364:
#line 4291 "zmac.y"
{
			if (yyvsp[0].exprptr->e_value < 0) {
				yyvsp[0].exprptr->e_value = -yyvsp[0].exprptr->e_value;
				yyval.exprptr = expr_mk(yyvsp[-2].exprptr, SHR, yyvsp[0].exprptr);
			}
			else
				yyval.exprptr = expr_mk(yyvsp[-2].exprptr, SHL, yyvsp[0].exprptr);
		;
    break;}
case 365:
#line 4301 "zmac.y"
{
			expr_number_check(yyvsp[-4].exprptr);
			if (yyvsp[-4].exprptr->e_value) {
				yyval.exprptr = yyvsp[-2].exprptr;
				expr_free(yyvsp[0].exprptr);
			}
			else {
				yyval.exprptr = yyvsp[0].exprptr;
				expr_free(yyvsp[-2].exprptr);
			}
			expr_free(yyvsp[-4].exprptr);
		;
    break;}
case 366:
#line 4315 "zmac.y"
{	yyval.exprptr = yyvsp[-1].exprptr;	;
    break;}
case 367:
#line 4318 "zmac.y"
{	yyval.exprptr = expr_op(yyvsp[0].exprptr, '~', 0, ~yyvsp[0].exprptr->e_value);	;
    break;}
case 368:
#line 4321 "zmac.y"
{	yyval.exprptr = expr_op(yyvsp[0].exprptr, '~', 0, ~yyvsp[0].exprptr->e_value);	;
    break;}
case 369:
#line 4324 "zmac.y"
{	yyval.exprptr = expr_op(yyvsp[0].exprptr, '!', 0, !yyvsp[0].exprptr->e_value * trueval);	;
    break;}
case 370:
#line 4327 "zmac.y"
{	yyval.exprptr = yyvsp[0].exprptr; /* no effect */	;
    break;}
case 371:
#line 4330 "zmac.y"
{	yyval.exprptr = yyvsp[0].exprptr; /* no effect */	;
    break;}
case 372:
#line 4333 "zmac.y"
{	yyval.exprptr = expr_op(yyvsp[0].exprptr, '-', 0, -yyvsp[0].exprptr->e_value);	;
    break;}
case 373:
#line 4336 "zmac.y"
{	yyval.exprptr = expr_op(yyvsp[0].exprptr, '-', 0, -yyvsp[0].exprptr->e_value);	;
    break;}
case 374:
#line 4339 "zmac.y"
{
			expr_reloc_check(yyvsp[0].exprptr);
			yyval.exprptr = expr_num(tstatesum[phaseaddr(yyvsp[0].exprptr->e_value)]);
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 375:
#line 4346 "zmac.y"
{
			int low;
			expr_reloc_check(yyvsp[0].exprptr);
			get_tstates(memory + phaseaddr(yyvsp[0].exprptr->e_value), &low, 0, 0, 0);
			yyval.exprptr = expr_num(low);
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 376:
#line 4355 "zmac.y"
{
			int high;
			expr_reloc_check(yyvsp[0].exprptr);
			get_tstates(memory + phaseaddr(yyvsp[0].exprptr->e_value), 0, &high, 0, 0);
			yyval.exprptr = expr_num(high);
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 377:
#line 4364 "zmac.y"
{
			expr_reloc_check(yyvsp[0].exprptr);
			yyval.exprptr = expr_num(ocfsum[phaseaddr(yyvsp[0].exprptr->e_value)]);
			expr_free(yyvsp[0].exprptr);
		;
    break;}
case 378:
#line 4371 "zmac.y"
{
			yyval.exprptr = expr_op(yyvsp[0].exprptr, LOW, 0, yyvsp[0].exprptr->e_value & 0xff);
		;
    break;}
case 379:
#line 4376 "zmac.y"
{
			yyval.exprptr = expr_op(yyvsp[0].exprptr, LOW, 0, yyvsp[0].exprptr->e_value & 0xff);
		;
    break;}
case 380:
#line 4381 "zmac.y"
{
			yyval.exprptr = expr_op(yyvsp[0].exprptr, HIGH, 0, (yyvsp[0].exprptr->e_value >> 8) & 0xff);
		;
    break;}
case 381:
#line 4386 "zmac.y"
{
			yyval.exprptr = expr_op(yyvsp[0].exprptr, HIGH, 0, (yyvsp[0].exprptr->e_value >> 8) & 0xff);
		;
    break;}
case 389:
#line 4409 "zmac.y"
{ int i;
		if (expptr >= MAXEXP)
			error("Macro expansion level too deep");
		est2 = (union exprec *) malloc((PARMMAX + PAREXT) * sizeof *est2);
		expstack[expptr] = est2;
		for (i=0; i<PARMMAX; i++)
			est2[i].param = 0;
		arg_start();
	;
    break;}
case 390:
#line 4422 "zmac.y"
{	arg_start();	;
    break;}
case 391:
#line 4426 "zmac.y"
{	arg_reset();	;
    break;}
case 392:
#line 4430 "zmac.y"
{	if (mras) mras_undecl_ok = 1; ;
    break;}
case 393:
#line 4434 "zmac.y"
{	if (mras) mras_undecl_ok = 0; ;
    break;}
}
   /* the action file gets copied in in place of this dollarsign */
#line 542 "bison.simple"

  yyvsp -= yylen;
  yyssp -= yylen;
#ifdef YYLSP_NEEDED
  yylsp -= yylen;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

  *++yyvsp = yyval;

#ifdef YYLSP_NEEDED
  yylsp++;
  if (yylen == 0)
    {
      yylsp->first_line = yylloc.first_line;
      yylsp->first_column = yylloc.first_column;
      yylsp->last_line = (yylsp-1)->last_line;
      yylsp->last_column = (yylsp-1)->last_column;
      yylsp->text = 0;
    }
  else
    {
      yylsp->last_line = (yylsp+yylen-1)->last_line;
      yylsp->last_column = (yylsp+yylen-1)->last_column;
    }
#endif

  /* Now "shift" the result of the reduction.
     Determine what state that goes to,
     based on the state we popped back to
     and the rule number reduced by.  */

  yyn = yyr1[yyn];

  yystate = yypgoto[yyn - YYNTBASE] + *yyssp;
  if (yystate >= 0 && yystate <= YYLAST && yycheck[yystate] == *yyssp)
    yystate = yytable[yystate];
  else
    yystate = yydefgoto[yyn - YYNTBASE];

  goto yynewstate;

yyerrlab:   /* here on detecting error */

  if (! yyerrstatus)
    /* If not already recovering from an error, report this error.  */
    {
      ++yynerrs;

#ifdef YYERROR_VERBOSE
      yyn = yypact[yystate];

      if (yyn > YYFLAG && yyn < YYLAST)
	{
	  int size = 0;
	  char *msg;
	  int x, count;

	  count = 0;
	  /* Start X at -yyn if nec to avoid negative indexes in yycheck.  */
	  for (x = (yyn < 0 ? -yyn : 0);
	       x < (sizeof(yytname) / sizeof(char *)); x++)
	    if (yycheck[x + yyn] == x)
	      size += strlen(yytname[x]) + 15, count++;
	  msg = (char *) malloc(size + 15);
	  if (msg != 0)
	    {
	      strcpy(msg, "parse error");

	      if (count < 5)
		{
		  count = 0;
		  for (x = (yyn < 0 ? -yyn : 0);
		       x < (sizeof(yytname) / sizeof(char *)); x++)
		    if (yycheck[x + yyn] == x)
		      {
			strcat(msg, count == 0 ? ", expecting `" : " or `");
			strcat(msg, yytname[x]);
			strcat(msg, "'");
			count++;
		      }
		}
	      yyerror(msg);
	      free(msg);
	    }
	  else
	    yyerror ("parse error; also virtual memory exceeded");
	}
      else
#endif /* YYERROR_VERBOSE */
	yyerror("parse error");
    }

  goto yyerrlab1;
yyerrlab1:   /* here on error raised explicitly by an action */

  if (yyerrstatus == 3)
    {
      /* if just tried and failed to reuse lookahead token after an error, discard it.  */

      /* return failure if at end of input */
      if (yychar == YYEOF)
	YYABORT;

#if YYDEBUG != 0
      if (yydebug)
	fprintf(stderr, "Discarding token %d (%s).\n", yychar, yytname[yychar1]);
#endif

      yychar = YYEMPTY;
    }

  /* Else will try to reuse lookahead token
     after shifting the error token.  */

  yyerrstatus = 3;		/* Each real token shifted decrements this */

  goto yyerrhandle;

yyerrdefault:  /* current state does not do anything special for the error token. */

#if 0
  /* This is wrong; only states that explicitly want error tokens
     should shift them.  */
  yyn = yydefact[yystate];  /* If its default is to accept any token, ok.  Otherwise pop it.*/
  if (yyn) goto yydefault;
#endif

yyerrpop:   /* pop the current state because it cannot handle the error token */

  if (yyssp == yyss) YYABORT;
  yyvsp--;
  yystate = *--yyssp;
#ifdef YYLSP_NEEDED
  yylsp--;
#endif

#if YYDEBUG != 0
  if (yydebug)
    {
      short *ssp1 = yyss - 1;
      fprintf (stderr, "Error: state stack now");
      while (ssp1 != yyssp)
	fprintf (stderr, " %d", *++ssp1);
      fprintf (stderr, "\n");
    }
#endif

yyerrhandle:

  yyn = yypact[yystate];
  if (yyn == YYFLAG)
    goto yyerrdefault;

  yyn += YYTERROR;
  if (yyn < 0 || yyn > YYLAST || yycheck[yyn] != YYTERROR)
    goto yyerrdefault;

  yyn = yytable[yyn];
  if (yyn < 0)
    {
      if (yyn == YYFLAG)
	goto yyerrpop;
      yyn = -yyn;
      goto yyreduce;
    }
  else if (yyn == 0)
    goto yyerrpop;

  if (yyn == YYFINAL)
    YYACCEPT;

#if YYDEBUG != 0
  if (yydebug)
    fprintf(stderr, "Shifting error token, ");
#endif

  *++yyvsp = yylval;
#ifdef YYLSP_NEEDED
  *++yylsp = yylloc;
#endif

  yystate = yyn;
  goto yynewstate;

 yyacceptlab:
  /* YYACCEPT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 0;

 yyabortlab:
  /* YYABORT comes here.  */
  if (yyfree_stacks)
    {
      free (yyss);
      free (yyvs);
#ifdef YYLSP_NEEDED
      free (yyls);
#endif
    }
  return 1;
}
#line 4437 "zmac.y"

/*extern int	yylval;*/

#define F_END	0
#define OTHER	1
#define SPACE	2
#define DIGIT	3
#define LETTER	4
#define STARTER 5
#define DOLLAR	6


/*
 *  This is the table of character classes.  It is used by the lexical
 *  analyser. (yylex())
 */
char	charclass[] = {
	F_END,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,
	OTHER,	SPACE,	OTHER,	OTHER,	OTHER,	SPACE,	OTHER,	OTHER,
	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,
	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,
	SPACE,	OTHER,	OTHER,	OTHER,	DOLLAR,	OTHER,	OTHER,	OTHER,	//  !"#$%&'
	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	STARTER,OTHER,	// ()*+,-./
	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	DIGIT,	// 01234567
	DIGIT,	DIGIT,	OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	STARTER,// 89:;<=>?
	STARTER,LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// @ABCDEFG
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// HIJKLMNO
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// PQRSTUVW
	LETTER, LETTER, LETTER, OTHER,	OTHER,	OTHER,	OTHER,	LETTER,	// XYZ[\]^_
	OTHER,	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// `abcdefg
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// hijklmno
	LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER, LETTER,	// pqrstuvw
	LETTER, LETTER, LETTER, OTHER,	OTHER,	OTHER,	OTHER,	OTHER,	// xyz{|}~
};
#define CHARCLASS(x) charclass[(x) & 0xff]


/*
 *  the following table tells which characters are parts of numbers.
 *  The entry is non-zero for characters which can be parts of numbers.
 */
char	numpart[] = {
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	'0',	'1',	'2',	'3',	'4',	'5',	'6',	'7',
	'8',	'9',	0,	0,	0,	0,	0,	0,
	0,	'A',	'B',	'C',	'D',	'E',	'F',	0,
	'H',	0,	0,	0,	0,	0,	0,	'O',
	0,	'Q',	0,	0,	0,	0,	0,	0,
	0,	0,	0,	0,	0,	0,	0,	0,
	0,	'a',	'b',	'c',	'd',	'e',	'f',	0,
	'h',	0,	0,	0,	0,	0,	0,	'o',
	0,	'q',	0,	0,	0,	0,	0,	0,
	'x',	0,	0,	0,	0,	0,	0,	0,
	0};




/*
 *  the following table is a list of assembler mnemonics;
 *  for each mnemonic the associated machine-code bit pattern
 *  and symbol type are given.
 *
 *  The i_uses field is overloaded to indicate the possible uses for
 *  a token.
 */

#define VERB	(1)	/* opcode or psuedo-op */
#define I8080	(2)	/* used in 8080 instructions */
#define Z80	(4)	/* used in Z80 instructions */
#define UNDOC	(8)	/* used only in undocumented instructions */
#define TERM	(16)	/* can appear in expressions (not all marked) */
#define ZNONSTD	(32)	/* non-standard Z-80 mnemonic (probably TDL or DRI) */
#define COL0	(64)	/* will always be recognized in logical column 0 */
#define MRASOP	(128)	/* dig operator out of identifiers */
#define Z180	(256)	/* used in Z180 (HD64180) instructions */

struct	item	keytab[] = {
	{"*get",	PSINC,	ARGPSEUDO,	VERB | COL0 },
	{"*include",	PSINC,	ARGPSEUDO,	VERB | COL0 },
	{"*list",	0,	LIST,		VERB | COL0 },
	{"*mod",	0,	MRAS_MOD,	VERB },
	{".8080",	0,	INSTSET,	VERB },
	{"a",		7,	ACC,		I8080 | Z80 },
	{"aci",		0316,	ALUI8,		VERB | I8080 },
	{"adc",		0210,	ARITHC,		VERB | I8080 | Z80  },
	{"adcx",	0xdd8e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"adcy",	0xfd8e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"add",		0200,	ADD,		VERB | I8080 | Z80  },
	{"addx",	0xdd86,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"addy",	0xfd86,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"adi",		0306,	ALUI8,		VERB | I8080 },
	{"af",		060,	AF,		Z80 },
	{"ana",		0240,	ARITHC,		VERB | I8080},
	{"and",		0240,	AND,		VERB | Z80 | TERM },
	{".and.",	0,	MROP_AND,	TERM | MRASOP },
	{"andx",	0xdda6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"andy",	0xfda6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"ani",		0346,	ALUI8,		VERB | I8080 },
	{".ascii",	0,	DEFB,		VERB },
	{".aseg",	SEG_ABS,SETSEG,		VERB },
	{".aset",	0,	DEFL,		VERB },
	{".assert",	0,	ASSERT,		VERB },
	{"b",		0,	REGNAME,	I8080 | Z80 },
	{"bc",		0,	RP,		Z80 },
	{"bit",		0145500,BIT,		VERB | Z80 },
	{"bitx",	0xddcb0046,BIT_XY,	VERB | Z80 | ZNONSTD },
	{"bity",	0xfdcb0046,BIT_XY,	VERB | Z80 | ZNONSTD },
	{".block",	0,	DEFS,		VERB },
	{".byte",	0,	DEFB,		VERB },
	{".bytes",	0,	DC,		VERB },
	{"c",		1,	TK_C,		I8080 | Z80 },
	{"call",	0315,	CALL,		VERB | I8080 | Z80 },
	{"cc",		0334,	CALL8,		VERB | I8080 },
	{"ccd",		0xeda9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ccdr",	0xedb9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ccf",		077,	NOOPERAND,	VERB | Z80 },
	{"cci",		0xeda1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ccir",	0xedb1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"cm",		0374,	CALL8,		VERB | I8080 },
	{"cma",		057,	NOOPERAND,	VERB | I8080 },
	{"cmc",		077,	NOOPERAND,	VERB | I8080 },
	{"cmp",		0270,	LOGICAL,	VERB | I8080 },
	{"cmpx",	0xddbe,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"cmpy",	0xfdbe,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"cnc",		0324,	CALL8,		VERB | I8080 },
	{"cnz",		0304,	CALL8,		VERB | I8080 },
	{".comment",	SPCOM,	SPECIAL,	VERB },
	{".common",	PSCMN,	ARGPSEUDO,	VERB },
	{".cond",	0,	IF_TK,		VERB },
	{"cp",		0270,	LOGICAL,	VERB | I8080 | Z80 },
	{"cpd",		0166651,NOOPERAND,	VERB | Z80 },
	{"cpdr",	0166671,NOOPERAND,	VERB | Z80 },
	{"cpe",		0354,	CALL8,		VERB | I8080 },
	{"cpi",		0166641,NOOPERAND,	VERB | I8080 | Z80 },
	{"cpir",	0166661,NOOPERAND,	VERB | Z80 },
	{"cpl",		057,	NOOPERAND,	VERB | Z80 },
	{"cpo",		0344,	CALL8,		VERB | I8080 },
	{".cseg",	SEG_CODE,SETSEG,	VERB },
	{"cz",		0314,	CALL8,		VERB | I8080 },
	{"d",		2,	REGNAME,	I8080 | Z80 },
	{".d3",		0,	DEF3,		VERB },
	{"daa",		0047,	NOOPERAND,	VERB | I8080 | Z80 },
	{"dad",		9,	DAD,		VERB | I8080 },
	{"dadc",	0xed4a,	ARITH16,	VERB | Z80 | ZNONSTD },
	{"dadx",	0xdd09,	ARITH16,	VERB | Z80 | ZNONSTD },
	{"dady",	0xfd09,	ARITH16,	VERB | Z80 | ZNONSTD },
	{".db",		0,	DEFB,		VERB },
	{".dc",		0,	DC,		VERB },
	{"dcr",		5,	INRDCR,		VERB | I8080 },
	{"dcrx",	0xdd35,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"dcry",	0xfd35,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"dcx",		0xb,	INXDCX,		VERB | I8080 },
	{"dcxix",	0xdd2b,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"dcxiy",	0xfd2b,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"de",		020,	RP,		Z80 },
	{"dec",		5,	INCDEC,		VERB | I8080 | Z80 },
	{".def3",	0,	DEF3,		VERB },
	{".defb",	0,	DEFB,		VERB },
	{".defd",	0,	DEFD,		VERB },
	{".defl",	0,	DEFL,		VERB },
	{".defm",	0,	DEFB,		VERB },
	{".defs",	0,	DEFS,		VERB },
	{".defw",	0,	DEFW,		VERB },
	{".dephase",	0,	DEPHASE,	VERB },
	{"di",		0363,	NOOPERAND,	VERB | I8080 | Z80 },
	{"djnz",	020,	DJNZ,		VERB | Z80 },
	{".dm",		0,	DEFB,		VERB },
	{".ds",		0,	DEFS,		VERB },
	{"dsbc",	0xed42,	ARITH16,	VERB | Z80 | ZNONSTD },
	{".dseg",	SEG_DATA,SETSEG,	VERB },
	{".dw",		0,	DEFW,		VERB },
	{".dword",	0,	DEFD,		VERB },
	{"e",		3,	REGNAME,	I8080 | Z80 },
	{"ei",		0373,	NOOPERAND,	VERB | I8080 | Z80 },
	{".eject",	1,	LIST,		VERB },
	{".elist",	3,	LIST,		VERB },
	{".else",	0,	ELSE_TK,	VERB },
	{".end",	0,	END,		VERB },
	{".endc",	0,	ENDIF_TK,	VERB },
	{".endif",	0,	ENDIF_TK,	VERB },
	{".endm", 	0,	ENDM,		VERB },
	{".entry",	0,	PUBLIC,		VERB },
	{"eq",		0,	EQ,		0 },
	{".eq.",	0,	MROP_EQ,	TERM | MRASOP },
	{".equ",	0,	EQU,		VERB },
	{"ex",		0xEB,	EX,		VERB | Z80 },
	{"exaf",	0x08,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{".exitm", 	0,	EXITM,		VERB },
	{".ext",	0,	EXTRN,		VERB },
	{".extern",	0,	EXTRN,		VERB },
	{".extrn",	0,	EXTRN,		VERB },
	{"exx",		0331,	NOOPERAND,	VERB | Z80 },
	{"f",		0,	TK_F,		Z80 },
	{".flist",	4,	LIST,		VERB },
	{"ge",		0,	GE,		0 },
	{".ge.",	0,	MROP_GE,	TERM | MRASOP },
	{".glist",	5,	LIST,		VERB },
	{".global",	0,	PUBLIC,		VERB },
	{"gt",		0,	GT,		0 },
	{".gt.",	0,	MROP_GT,	TERM | MRASOP },
	{"h",		4,	REGNAME,	I8080 | Z80 },
	{"halt",	0166,	NOOPERAND,	VERB | Z80 },
	{"high",	0,	HIGH,		0 },
	{".high.",	0,	MROP_HIGH,	TERM | MRASOP },
	{"hl",		040,	HL,		Z80 },
	{"hlt",		0166,	NOOPERAND,	VERB | I8080 },
	{"hx",   	0x1DD04,IXYLH,		Z80 | UNDOC },
	{"hy",   	0x1FD04,IXYLH,		Z80 | UNDOC },
	{"i",		0,	MISCREG,	Z80 },
	{".if",		0,	IF_TK,		VERB | COL0 },
	{".if1",	0,	IF1_TK,		VERB | COL0 },
	{".if2",	0,	IF2_TK,		VERB | COL0 },
	{".ifdef",	1,	IF_DEF_TK,	VERB | COL0 },
	{".ife",	0,	IFE_TK,		VERB | COL0 },
	{".ifeq",	'=',	IF_CP_TK,	VERB | COL0 },
	{".iff",	0,	IFE_TK,		VERB | COL0 },
	{".ifgt",	'>',	IF_CP_TK,	VERB | COL0 },
	{".iflt",	'<',	IF_CP_TK,	VERB | COL0 },
	{".ifndef",	0,	IF_DEF_TK,	VERB | COL0 },
	{".ifne",	NE,	IF_CP_TK,	VERB | COL0 },
	{".ift",	0,	IF_TK,		VERB | COL0 },
	{"im",		0166506,IM,		VERB | Z80 },
	{"im0",		0xed46,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"im1",		0xed56,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"im2",		0xed5e,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{".import",	PSIMPORT,ARGPSEUDO,	VERB | COL0 },
	{"in",		0333,	TK_IN,		VERB | I8080 | Z80 },
	{"in0",		0xED00,	TK_IN0,		VERB | Z180 },
	{"inc",		4,	INCDEC,		VERB | Z80 },
	{".incbin", 	0, 	INCBIN,		VERB },
	{".include",	PSINC,	ARGPSEUDO,	VERB | COL0 },	// COL0 only needed for MRAS mode
	{"ind",		0166652,NOOPERAND,	VERB | Z80 },
	{"indr",	0166672,NOOPERAND,	VERB | Z80 },
	{"ini",		0166642,NOOPERAND,	VERB | Z80 },
	{"inir",	0166662,NOOPERAND,	VERB | Z80 },
	{"inp",		0xed40,	INP,		VERB | Z80 | ZNONSTD },
	{"inr",		4,	INRDCR,		VERB | I8080 },
	{"inrx",	0xdd34,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"inry",	0xfd34,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"inx",		3,	INXDCX,		VERB | I8080 },
	{"inxix",	0xdd23,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"inxiy",	0xfd23,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"irp",		0,	IRP,		VERB },
	{"irpc",	0,	IRPC,		VERB },
	{"ix",		0156440,INDEX,		Z80 },
	{"ixh",		0x1DD04,IXYLH,		Z80 | UNDOC },
	{"ixl",		0x1DD05,IXYLH,		Z80 | UNDOC },
	{"iy",		0176440,INDEX,		Z80 },
	{"iyh",		0x1FD04,IXYLH,		Z80 | UNDOC },
	{"iyl",		0x1FD05,IXYLH,		Z80 | UNDOC },
	{"jc",		0332,	JUMP8,		VERB | I8080 },
	{"jm",		0372,	JUMP8,		VERB | I8080 },
	{"jmp",		0303,	JP,		VERB | I8080 },
	{"jnc",		0322,	JUMP8,		VERB | I8080 },
	{"jnz",		0302,	JUMP8,		VERB | I8080 },
	{"jp",		0362,	JP,		VERB | I8080 | Z80 },
	{"jpe",		0352,	JUMP8,		VERB | I8080 },
	{".jperror",	0,	JPERROR,	VERB },
	{"jpo",		0342,	JUMP8,		VERB | I8080 },
	{"jr",		040,	JR,		VERB | Z80 },
	{"jrc",		0x38,	JR_COND,	VERB | Z80 | ZNONSTD },
	{"jrnc",	0x30,	JR_COND,	VERB | Z80 | ZNONSTD },
	{"jrnz",	0x20,	JR_COND,	VERB | Z80 | ZNONSTD },
	{".jrpromote",	0,	JRPROMOTE,	VERB },
	{"jrz",		0x28,	JR_COND,	VERB | Z80 | ZNONSTD },
	{"jz",		0312,	JUMP8,		VERB | I8080 },
	{"l",		5,	REGNAME,	I8080 | Z80 },
	{".lall",	0,	LALL,		VERB | COL0 },
	{"lbcd",	0xed4b,	LDST16,		VERB | Z80 | ZNONSTD },
	{"ld",		0x40,	LD,		VERB | Z80 },
	{"lda",		0x3a,	LDA,		VERB | I8080 },
	{"ldai",	0xed57,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ldar",	0xed5f,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"ldax",	0xA,	LDAX,		VERB | I8080 },
	{"ldd",		0166650,NOOPERAND,	VERB | Z80 },
	{"lddr",	0166670,NOOPERAND,	VERB | Z80 },
	{"lded",	0xed5b,	LDST16,		VERB | Z80 | ZNONSTD },
	{"ldi",		0166640,NOOPERAND,	VERB | Z80 },
	{"ldir",	0166660,NOOPERAND,	VERB | Z80 },
	{"ldx",		0xdd46,	LD_XY,		VERB | Z80 | ZNONSTD},
	{"ldy",		0xfd46,	LD_XY,		VERB | Z80 | ZNONSTD},
	{"le",		0,	LE,		0 },
	{".le.",	0,	MROP_LE,	TERM | MRASOP },
	{"lhld",	0x2a,	LHLD,		VERB | I8080 },
	{".list",	0,	LIST,		VERB | COL0 }, // COL0 only needed for MRAS
	{"lixd",	0xdd2a,	LDST16,		VERB | Z80 | ZNONSTD },
	{"liyd",	0xfd2a,	LDST16,		VERB | Z80 | ZNONSTD },
	{".local",	0,	LOCAL,		VERB },
	{"low",		0,	LOW,		0 },
	{".low.",	0,	MROP_LOW,	TERM | MRASOP },
	{"lspd",	0xed7b,	LDST16,		VERB | Z80 | ZNONSTD },
	{"lt",		0,	LT,		0 },
	{".lt.",	0,	MROP_LT,	TERM | MRASOP },
	{"lx",   	0x1DD05,IXYLH,		Z80 | UNDOC },
	{"lxi",		1,	LXI,		VERB | I8080 },
	{"lxix",	0xdd21,	LDST16,		VERB | Z80 | ZNONSTD },
	{"lxiy",	0xfd21,	LDST16,		VERB | Z80 | ZNONSTD },
	{"ly",   	0x1FD05,IXYLH,		Z80 | UNDOC },
	{"m",		070,	COND,		I8080 | Z80 },
	{".maclib",	PSMACLIB,ARGPSEUDO,	VERB },
	{".macro",	0,	MACRO,		VERB },
	{".max",	1,	MINMAX,		VERB },
	{".min",	0,	MINMAX,		VERB },
	{".mlist",	6,	LIST,		VERB },
	{"mlt",		0xED4C,	MLT,		VERB | Z180 },
	{"mod",		0,	'%',		0 },
	{".mod.",	0,	MROP_MOD,	TERM | MRASOP },
	{"mov",		0x40,	MOV,		VERB | I8080 },
	{"mvi",		6,	MVI,		VERB | I8080 },
	{"mvix",	0xdd36,	MV_XY,		VERB | Z80 | ZNONSTD },
	{"mviy",	0xfd36,	MV_XY,		VERB | Z80 | ZNONSTD },
	{".name",	SPNAME,	SPECIAL,	VERB },
	{"nc",		020,	SPCOND,		0 },
	{"ne",		0,	NE,		0 },
	{".ne.",	0,	MROP_NE,	TERM | MRASOP },
	{"neg",		0166504,NOOPERAND,	VERB | Z80 },
	{".nolist",	-1,	LIST,		VERB },
	{"nop",		0,	NOOPERAND,	VERB | I8080 | Z80 },
	{"not",		0,	'~',		0 },
	{".not.",	0,	MROP_NOT,	TERM | MRASOP },
	{"nul",		0,	NUL,		0 },
	{"nv",		040,	COND,		Z80 },
	{"nz",		0,	SPCOND,		Z80 },
	{"ocf",		0,	OCF,		0 },
	{"or",		0260,	OR,		VERB | Z80 | TERM },
	{".or.",	6,	MROP_OR,	TERM | MRASOP },
	{"ora",		0260,	LOGICAL,	VERB | I8080 },
	{".org",	0,	ORG,		VERB },
	{"ori",		0366,	ALUI8,		VERB | I8080 },
	{"orx",		0xddb6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"ory",		0xfdb6,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"otdm",	0xED8B,	NOOPERAND,	VERB | Z180 },
	{"otdmr",	0xED9B,	NOOPERAND,	VERB | Z180 },
	{"otdr",	0166673,NOOPERAND,	VERB | Z80 },
	{"otim",	0xED83,	NOOPERAND,	VERB | Z180 },
	{"otimr",	0xED93,	NOOPERAND,	VERB | Z180 },
	{"otir",	0166663,NOOPERAND,	VERB | Z80 },
	{"out",		0323,	TK_OUT,		VERB | I8080 | Z80 },
	{"out0",	0xED01,	TK_OUT0,	VERB | Z180 },
	{"outd",	0166653,NOOPERAND,	VERB | Z80 },
	{"outdr",	0166673,NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"outi",	0166643,NOOPERAND,	VERB | Z80 },
	{"outir",	0166663,NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"outp",	0xED41,	OUTP,		VERB | Z80 | ZNONSTD },
	{"p",		060,	COND,		Z80 },
	{".page",	1,	LIST,		VERB },
	{"pchl",	0351,	NOOPERAND,	VERB | I8080 },
	{"pcix",	0xdde9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pciy",	0xfde9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pe",		050,	COND,		Z80 },
	{"pfix",	0xdd,	NOOPERAND,	VERB | Z80 | UNDOC },
	{"pfiy",	0xfd,	NOOPERAND,	VERB | Z80 | UNDOC },
	{".phase",	0,	PHASE,		VERB },
	{"po",		040,	COND,		Z80 },
	{"pop",		0301,	PUSHPOP,	VERB | I8080 | Z80 },
	{"popix",	0xdde1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"popiy",	0xfde1,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pragma",	SPPRAGMA,SPECIAL,	VERB },
	{".printx",	SPRINTX,	SPECIAL,	VERB | COL0 },
	{"psw", 	060,	PSW,		I8080 },
	{".public",	0,	PUBLIC,		VERB },
	{"push",	0305,	PUSHPOP,	VERB | I8080 | Z80 },
	{"pushix",	0xdde5,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"pushiy",	0xfde5,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"r",		010,	MISCREG,	Z80 },
	{"ral",		027,	NOOPERAND,	VERB | I8080 },
	{"ralr",	0xCB10,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"ralx",	0xddcb0016,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"raly",	0xfdcb0016,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rar",		037,	NOOPERAND,	VERB | I8080 },
	{"rarr",	0xCB18,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"rarx",	0xddcb001e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rary",	0xfdcb001e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rc",		0330,	NOOPERAND,	VERB | I8080 },
	{".read",	PSINC,	ARGPSEUDO,	VERB },
	{".rept",	0,	REPT,		VERB },
	{"res",		0145600,BIT,		VERB | Z80 },
	{"resx",	0xddcb0086,BIT_XY,	VERB | Z80 | ZNONSTD },
	{"resy",	0xfdcb0086,BIT_XY,	VERB | Z80 | ZNONSTD },
	{"ret",		0311,	RET,		VERB | I8080 | Z80 },
	{"reti",	0166515,NOOPERAND,	VERB | Z80 },
	{"retn",	0166505,NOOPERAND,	VERB | Z80 },
	{"rl",		0xCB10,	SHIFT,		VERB | Z80 },
	{"rla",		027,	NOOPERAND,	VERB | Z80 },
	{"rlc",		0xCB00,	SHIFT,		VERB | I8080 | Z80 },
	{"rlca",	07,	NOOPERAND,	VERB | Z80 },
	{"rlcr",	0xCB00,	SHIFT,		VERB | I8080 | Z80 | ZNONSTD },
	{"rlcx",	0xddcb0006,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rlcy",	0xfdcb0006,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rld",		0166557,NOOPERAND,	VERB | Z80 },
	{"rm",		0370,	NOOPERAND,	VERB | I8080 },
	{".rmem",	0,	DEFS,		VERB },
	{"rnc",		0320,	NOOPERAND,	VERB | I8080 },
	{"rnz",		0300,	NOOPERAND,	VERB | I8080 },
	{"rp",		0360,	NOOPERAND,	VERB | I8080 },
	{"rpe",		0350,	NOOPERAND,	VERB | I8080 },
	{"rpo",		0340,	NOOPERAND,	VERB | I8080 },
	{"rr",		0xCB18,	SHIFT,		VERB | Z80 },
	{"rra",		037,	NOOPERAND,	VERB | Z80 },
	{"rrc",		0xCB08,	SHIFT,		VERB | I8080 | Z80 },
	{"rrca",	017,	NOOPERAND,	VERB | Z80 },
	{"rrcr",	0xCB08,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"rrcx",	0xddcb000e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rrcy",	0xfdcb000e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"rrd",		0166547,NOOPERAND,	VERB | Z80 },
	{"rst",		0307,	RST,		VERB | I8080 | Z80 },
	{".rsym",	PSRSYM,	ARGPSEUDO,	VERB },
	{"rz",		0310,	NOOPERAND,	VERB | I8080 },
	{".sall",	0,	SALL,		VERB | COL0 },
	{"sbb",		0230,	ARITHC,		VERB | I8080 },
	{"sbc",		0230,	ARITHC,		VERB | Z80 },
	{"sbcd",	0xed43,	LDST16,		VERB | Z80 | ZNONSTD },
	{"sbcx",	0xdd9e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"sbcy",	0xfd9e,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"sbi",		0336,	ALUI8,		VERB | I8080 },
	{"scf",		067,	NOOPERAND,	VERB | Z80 },
	{"sded",	0xed53,	LDST16,		VERB | Z80 | ZNONSTD },
	{"set",		0145700,BIT,		VERB | Z80 },
	{"setb",	0145700,BIT,		VERB | Z80 | ZNONSTD },
	{".setocf",	0,	SETOCF,		VERB },
	{".sett",	0,	TSTATE,		VERB },
	{"setx",	0xddcb00c6,BIT_XY,	VERB | Z80 | ZNONSTD },
	{"sety",	0xfdcb00c6,BIT_XY,	VERB | Z80 | ZNONSTD },
	{"shl",		0,	SHL,		TERM },
	{".shl.",	0,	MROP_SHL,	TERM | MRASOP },
	{"shld",	0x22,	SHLD,		VERB | I8080 },
	{"shr",		0,	SHR,		TERM },
	{".shr.",	0,	MROP_SHR,	TERM | MRASOP },
	{"sixd",	0xdd22,	LDST16,		VERB | Z80 | ZNONSTD },
	{"siyd",	0xfd22,	LDST16,		VERB | Z80 | ZNONSTD },
	{"sl1",		0xCB30,	SHIFT,		VERB | Z80 | UNDOC },
	{"sla",		0xCB20,	SHIFT,		VERB | Z80 },
	{"slar",	0xCB20,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"slax",	0xddcb0026,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"slay",	0xfdcb0026,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"sll",		0xCB30,	SHIFT,		VERB | Z80 },
	{"slp",		0xED76,	NOOPERAND,	VERB | Z180 },
	{"sp",		060,	SP,		I8080 | Z80 },
	{".space",	2,	LIST,		VERB },
	{"sphl",	0371,	NOOPERAND,	VERB | I8080 },
	{"spix",	0xddf9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"spiy",	0xfdf9,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"sra",		0xCB28,	SHIFT,		VERB | Z80 },
	{"srar",	0xCB28,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"srax",	0xddcb002e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"sray",	0xfdcb002e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"srl",		0xCB38,	SHIFT,		VERB | Z80 },
	{"srlr",	0xCB38,	SHIFT,		VERB | Z80 | ZNONSTD },
	{"srlx",	0xddcb003e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"srly",	0xfdcb003e,SHIFT_XY,	VERB | Z80 | ZNONSTD },
	{"sspd",	0xed73,	LDST16,		VERB | Z80 | ZNONSTD },
	{"sta",		0x32,	STA,		VERB | I8080 },
	{"stai",	0xed47,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"star",	0xed4f,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"stax",	2,	STAX,		VERB | I8080 },
	{"stc",		067,	NOOPERAND,	VERB | I8080 },
	{"stx",		0xdd70,	ST_XY,		VERB | Z80 | ZNONSTD},
	{"sty",		0xfd70,	ST_XY,		VERB | Z80 | ZNONSTD},
	{"sub",		0220,	LOGICAL,	VERB | I8080 | Z80 },
	{".subttl",	SPSBTL,	SPECIAL,	VERB | COL0 },
	{"subx",	0xdd96,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"suby",	0xfd96,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"sui",		0326,	ALUI8,		VERB | I8080 },
	{"t",		0,	T,		0 },
	{".text",	0,	DEFB,		VERB },
	{"tihi",	0,	TIHI,		0 },
	{"tilo",	0,	TILO,		0 },
	{".title",	SPTITL,	SPECIAL,	VERB | COL0},
	{"tst",		0xED04,	TST,		VERB | Z180 },
	{".tstate",	0,	TSTATE,		VERB },
	{"tstio",	0xED74,	TSTIO,		VERB | Z180 },
	{"v",		050,	COND,		Z80 },
	{".word",	0,	DEFW,		VERB },
	{".wsym",	PSWSYM,	ARGPSEUDO,	VERB },
	{".xall",	0,	XALL,		VERB | COL0 },
	{"xchg",	0353,	NOOPERAND,	VERB | I8080 },
	{"xh",   	0x1DD04,IXYLH,		Z80 | UNDOC },
	{"xl",   	0x1DD05,IXYLH,		Z80 | UNDOC },
	{"xor",		0250,	XOR,		VERB | Z80 | TERM },
	{".xor.",	0,	MROP_XOR,	TERM | MRASOP },
	{"xorx",	0xddae,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"xory",	0xfdae,	ALU_XY,		VERB | Z80 | ZNONSTD },
	{"xra",		0250,	LOGICAL,	VERB | I8080 },
	{"xri",		0356,	ALUI8,		VERB | I8080 },
	{"xthl",	0343,	NOOPERAND,	VERB | I8080 },
	{"xtix",	0xdde3,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"xtiy",	0xfde3,	NOOPERAND,	VERB | Z80 | ZNONSTD },
	{"yh",   	0x1FD04,IXYLH,		Z80 | UNDOC },
	{"yl",   	0x1FD05,IXYLH,		Z80 | UNDOC },
	{"z",		010,	SPCOND,		Z80 },
	{".z180",	2,	INSTSET,	VERB },
	{".z80",	1,	INSTSET,	VERB },
};

/*
 *  user-defined items are tabulated in the following table.
 */

struct item	itemtab[ITEMTABLESIZE];
struct item	*itemmax = itemtab+ITEMTABLESIZE;

int item_is_verb(struct item *i)
{
	return i && (i->i_uses & VERB) == VERB;
}

int item_value(struct item *i)
{
	int value = i->i_value;

	// Some special cases for 8080 opcode values.
	if (!z80) {
		// CP is CALL P in 8080
		if (i->i_value == 0270 && i->i_string[1] == 'p')
			value = 0364;
		else if (i->i_value == 0166641) // CPI
			value = 0376;
		else if (i->i_token == SHIFT && (i->i_value & 070) < 020)
			value = 7 | (i->i_value & 070);
	}
	else {
		if (i->i_token == JR)
			value = 0x18;
		else if (i->i_token == JP)
			value = 0xC3;

		value = sized_byteswap(value);
	}

	return value;
}

/*
 *  lexical analyser, called by yyparse.
 */
int yylex()
{
	int lex();
	int token = lex();

	if (mras) {
		switch (token)
		{
		// Operator translations because of different precedence
		case '+': token = MROP_ADD; break;
		case '-': token = MROP_SUB; break;
		case '*': token = MROP_MUL; break;
		case '/': token = MROP_DIV; break;
		case '%': token = MROP_MOD; break;
		case '&': token = MROP_AND; break;
		case '|': token = MROP_OR; break;
		case '^': token = MROP_XOR; break;
		case SHL: token = MROP_SHL; break;
		case SHR: token = MROP_SHR; break;
		case LT:  token = MROP_LT; break;
		case EQ:  token = MROP_EQ; break;
		case '>': token = MROP_GT; break;
		case GE:  token = MROP_GE; break;
		case NE:  token = MROP_NE; break;
		case LE:  token = MROP_LE; break;
		case NOT: token = MROP_NOT; break;
		case HIGH: token = MROP_HIGH; break;
		case LOW: token = MROP_LOW; break;
		// Operator translations to completely different operator.
		case '<': token = MROP_SHIFT; break;
		case '!': token = MROP_OR; break;
		default: break;
		// Sadly, AND, OR, XOR and '=' can't be translated unilaterally
		// because they are also opcodes or psuedo-ops.
		}
	}

	return token;
}

int lex()
{
	int c;
	char *p;
	int radix;
	int sep;
	int exclude, include, overflow, token, endc;

	if (arg_flag) {
		yylval.cval = arg_state.arg;
		c = getarg(&arg_state);
		if (c == '\0' || c == '\n' || c == ';')
			c = skipline(c);

		return c;
	}

	if (raw == 2) {
		while (charclass[c = nextchar()] == SPACE)
			;

		*tempbuf = c == '\n' || c == '\0';

		peekc = skipline(c);

		raw = 0;

		return RAWTOKEN;
	}
	else if (raw) {
		int skip = 1;
		p = tempbuf;
		while ((c = nextchar()) != '\n' && c) {
			if (p >= tempmax) {
				*p = '\0';
				printf("was parsing '%s'\n", tempbuf);
				error(symlong);
			}
			if (!skip || charclass[c] != SPACE) {
				*p++ = c;
				skip = 0;
			}
		}
		if (c == 0)
			peekc = c;

		*p-- = '\0';

		while (p >= tempbuf && CHARCLASS(*p) == SPACE)
			*p-- = '\0';

		raw = 0;

		return RAWTOKEN;
	}

	for (;;) switch(charclass[c = nextchar()]) {
	case F_END:
		if (!expptr)
			return 0;

		if (est[MSTR].param) {
			int ch;
			est[REPNUM].value++;
			ch = est[MSTR].param[est[REPNUM].value];
			if (ch) {
				est[0].param[0] = ch;
				floc = est[MSTART].value;
				mfseek(mfile, (long)floc, 0);
				est[TEMPNUM].value = exp_number++;
			}
			else {
				free(est[MSTR].param);
				est[MSTR].param = 0;
				popsi();
			}
		}
		else if (est[REPNUM].value < 0) {
			int arg;
			do {
				switch (getarg(est[MARGP].ap)) {
				case ARG:
					arg = 1;
					break;
				case ',':
					arg = 0;
					break;
				default:
					arg = 2;
					break;
				}
			} while (!arg);

			if (arg == 1) {
				floc = est[MSTART].value;
				mfseek(mfile, (long)floc, 0);
				est[TEMPNUM].value = exp_number++;
			}
			else {
				// XXX - memory leak
				est[0].param = NULL;
				free(est[MARGP].ap);
				popsi();
			}
		}
		else if (est[REPNUM].value-- > 0) {
			floc = est[MSTART].value;
			mfseek(mfile, (long)floc, 0);
			est[TEMPNUM].value = exp_number++;
		}
		else
			popsi();

		continue;

	case SPACE:
		while (charclass[c = nextchar()] == SPACE)
			;
		peekc = c;
		logcol++;
		break;
	case LETTER:
	case STARTER:
	case DIGIT:
	case DOLLAR:
	spectok:
		firstcol = getcol() == 1;

		radix = -1; // might be a number
		p = tempbuf;
		do {
			if (p >= tempmax) {
				*tempmax = '\0';
				printf("was parsing '%s'\n", tempbuf);
				error(symlong);
			}

			if (driopt && c == '$') {
				c = nextchar();
				continue;
			}
			// GWP - don't lowercase
			//*p = (c >= 'A' && c <= 'Z') ? c + 'a' - 'A' : c;
			*p = c;
			if (mras && *p == '?') {
				char *q;

				radix = 0; // can't be a number even if it looks like it

				if (expptr)
					q = getmraslocal();
				else
					for (q = modstr; *q == '@'; q++)
						;

				if (*q) {
					strcpy(p, q);
					p = strchr(p, '\0') - 1;
				}
				else
					*p = '?';
			}
			p++;
			c = nextchar();
		} while	(charclass[c]==LETTER || charclass[c]==DIGIT ||
			charclass[c]==STARTER || charclass[c]==DOLLAR);

		if (driopt && p == tempbuf)
			*p++ = '$'; // reverse overzelous stripping

		*p = '\0';

		// When parsing macro parameters we use a custom symbol table.
		// And, heck, almost anything goes.
		if (param_parse) {
			struct item *param = item_lookup(tempbuf, paramtab, PARAMTABSIZE);
			peekc = c;
			if (param->i_token) {
				sprintf(detail, "%s error.  Macro parameter '%s' repeated",
					errname[fflag], tempbuf);
				errwarn(fflag, detail);
			}

			param->i_token = MPARM;
			param->i_string = malloc(strlen(tempbuf) + 1);
			strcpy(param->i_string, tempbuf);

			yylval.itemptr = param;
			return param->i_token;
		}

		// Special case for AF'
		if (c == '\'' && ci_strcmp(tempbuf, "af") == 0)
			return AFp;

		endc = c;
		peekc = c;

		// Pass off '?' (XXX but, technically, should only be done in expression context)
		if (strcmp(tempbuf, "?") == 0)
			return '?';

		// Pass off '$'
		if (strcmp(tempbuf, "$") == 0)
			return '$';

		// Look ahead at what we have.
		while (charclass[c] == SPACE)
			c = nextchar();

		peekc = c;

		//printf("%d %s\n", logcol, tempbuf);
		// If logcol == 0 then if c == ':' we're a label for sure.
		// If logcol == 1 if c == ':' we're a label, change logcol
		//    otherwise we're op or pseudo
		// If logcol == 0 and c == '\n' or ';' then we're alone so
		//	we give tokenization a chance otherwise label
		// If logcol >= 2 we're in the arguments
		//
		// There is quite a lot of unrealized scope for error
		// detection and helpful warnings.

		 // Default to any tokenization.
		exclude = 0;
		include = 0;

		if (logcol >= 2) {
			// Arguments allow mnemonics and psuedo-ops
			exclude = VERB;
			include = TERM;
		}
		else if (logcol == 0 && first_always_label) {
			exclude = ~TERM;
		}
		else if (logcol <= 1 && c == ':') {
			exclude = ~TERM;
			logcol = 0;
		}
		else if (logcol == 0 && c != ';' && c != '\n') {
			exclude = ~TERM;
			include = COL0;
		}

		logcol++;

		// Look for possible numbers.
		// 0x<hex> $<hex> <hex>h <octal>o <octal>q <binary>b
		// <decimal> <decimal>d
		// Suffix formats must start with 0-9.

		if (radix)
			radix = convert(tempbuf, p, &overflow);

		// If we're in the first logical column and the token starts with
		// '$' then we'll force it to be a label even though it could be
		// a $hex constant. This will allow $FCB as a label.
		// Thus we must also allow symbol lookup a chance to override number
		// parsing if we start with a '$'.

		if (tempbuf[0] == '$') {
			if (logcol == 1 || locate(tempbuf)->i_token) {
				if (radix > 0) {
					sprintf(detail, "warning: $hex constant '%s' interpreted as symbol", tempbuf);
					errwarn(warn_hex, detail);
				}
				radix = 0;
			}
		}

		if (radix > 0) {
			// Might be line skipping time, though.
			if (*ifptr)
				return skipline(c);

			if (overflow) {
				err[iflag]++;
				yylval.ival = 0;
			}
			return NUMBER;
		}

		// Too late to do '$' concatenation of numbers.  But zmac
		// didn't allow for that previously at any rate.
		if (zcompat) {
			char *q = tempbuf;
			// Normal zmac operation requires we ignore $ in identifiers
			for (p = q; *p; p++)
				if (*p != '$')
					*q++ = *p;

			*q = '\0';
			p = q;
		}

		// GWP - boy, this should be a warning or error
		if (p - tempbuf > MAXSYMBOLSIZE) {
			p = tempbuf + MAXSYMBOLSIZE;
			*p = '\0';
		}

		token = tokenofitem(UNDECLARED, exclude, include);

		// Initial "priming" hack

		if (endc == '\'')
		{
			//printf("allowing <<%s%c>> at %d, endc=%c\n", tempbuf, peekc, logcol, endc);
			peekc = NOPEEK;
// A step towards emitting the instructions
#if 0
			// Only if auto-exx on on...
			if (tempbuf[0] == 'a') {
				emit1(8, 0, 0, ET_NOARG);
				list_out(dollarsign, "\tex\taf,af'\n", '*');
			}
			else {
				emit1(0xd9, 0, 0, ET_NOARG);
				list_out(dollarsign, "\texx\n", '*');
			}
#endif
		}

		return token;

	default:
		if (*ifptr)
			return(skipline(c));

		if (mras && getcol() == 1 && c == '*')
			goto spectok;

		switch(c) {
		int corig;
		case ':':
			if (logcol == 1) {
				// Make sure "label:ret", "label: ret",
				// "label: :ret", "label: : ret" work out OK.
				// But stop fooling around once we've done the VERB
				peekc = nextchar();
				if (charclass[peekc] == SPACE)
					logcol--;
			}
			return c;
		case ';':
			return(skipline(c));
		case '\'':
		case '"':
			sep = c;
			p = tempbuf;
			p[1] = 0;
			do	switch(c = nextchar())	{
			case '\0':
			case '\n':
				err[bflag]++;
				goto retstring;
			default:
				if (c == sep && (c = nextchar()) != sep) {
				retstring:
					peekc = c;
					*p = '\0';
					switch (p - tempbuf) {
					case 2:
						p = tempbuf;
						yylval.ival = *p++ & 255;
						yylval.ival |= (*p & 255) << 8;
						return TWOCHAR;
					case 1:
						p = tempbuf;
						yylval.ival = *p++;
						return ONECHAR;
					case 0:
						if (!full_exprs) {
							yylval.ival = 0;
							return NUMBER;
						}
						// fall through
					default:
						yylval.cval = tempbuf;
						return STRING;
					}
				}
				*p++ = c;
			} while (p < tempmax);
			/*
			 *  if we break out here, our string is longer than
			 *  our input line
			 */
			error("string buffer overflow");
		case '<':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return LE;
			case '<':
				return SHL;
			case '>':
				return NE;
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '>':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return GE;
			case '>':
				return SHR;
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '!':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return NE;
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '=':
			corig = c;
			switch (c = nextchar ()) {
			case '=':
				return '=';
			default:
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */

		case '&':
			corig = c;
			if ((c = nextchar()) == '&')
				return ANDAND;
			else {
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		case '|':
			corig = c;
			if ((c = nextchar()) == '|')
				return OROR;
			else {
				peekc = c;
				return corig;
			}
			/* break; suppress "unreachable" warning for tcc */
		default:
			return(c);
		}
	}
}

// Convert string to number
// 0x<hex> $<hex> <hex>h <octal>o <octal>q <binary>b
// <decimal> <decimal>d
// Suffix formats must start with 0-9.
//
// Returns:
//	-1	not numeric
//	0	numeric but digit out of range
//	>0	radix of number,  yylval.ival holds value

int convert(char *buf, char *bufend, int *overflow)
{
	int radix = -1, dummy;
	char *d0, *dn;

	if (!bufend)
		bufend = strchr(buf, '\0');

	if (!overflow)
		overflow = &dummy;

	if (buf[0] == '0' && (buf[1] == 'x' || buf[1] == 'X') && buf[2]) {
		radix = 16;
		d0 = buf + 2;
		dn = bufend;
	} else if (buf[0] == '$') {
		radix = 16;
		d0 = buf + 1;
		dn = bufend;
	}
	else if (buf[0] >= '0' && buf[0] <= '9') {
		d0 = buf;
		dn = bufend - 1;
		switch (*dn) {
		case 'O':
		case 'o':
		case 'Q':
		case 'q':
			radix = 8;
			break;
		case 'D':
		case 'd':
			radix = 10;
			break;
		case 'H':
		case 'h':
			radix = 16;
			break;
		case 'B':
		case 'b':
			radix = 2;
			break;
		default:
			radix = 10;
			dn++;
			break;
		}
	}

	// We may have a number on our hands.
	if (radix > 0) {
		*overflow = 0;
		yylval.ival = 0;

		for (; d0 < dn; d0++) {
			unsigned int ovchk = (unsigned int)yylval.ival;
			int c = *d0;
			if (c >= 'a') c -= 'a' - 10;
			else if (c >= 'A') c -= 'A' - 10;
			else c -= '0';
			if (c < 0 || c >= radix) {
				radix = 0;
				break;
			}
			if (ovchk * radix / radix != ovchk)
				*overflow = 1;

			yylval.ival *= radix;
			yylval.ival += c;
		}
	}

	return radix;
}

// Verify keytab is in alphabetical order.
// And that all MRASOP keywords start with '.'

int check_keytab()
{
	int i;
	char *prev;

	for (i = 0; i < sizeof(keytab) / sizeof(keytab[0]); i++) {
		char *next = keytab[i].i_string;
		next += *next == '.';
		if (i != 0) {
			if (strcmp(prev, next) >= 0) {
				printf("keytab error: %s >= %s\n", prev, next);
				return 0;
			}
		}
		prev = next;

		if ((keytab[i].i_uses & MRASOP) && keytab[i].i_string[0] != '.') {
			printf("keytab error: %s does not start with '.'\n",
				keytab[i].i_string);
			return 0;
		}

		// Uncomment to list all 8080 verbs to assist documentation.
		//if ((keytab[i].i_uses & (VERB | I8080)) == (VERB | I8080))
		//	printf("\tdb\t%s\n", keytab[i].i_string);
		// Uncomment to list all Z-80 verbs to assist documentation.
		//if ((keytab[i].i_uses & (VERB | Z80)) == (VERB | Z80))
		//	printf("%-6s   $%X\n", keytab[i].i_string,
		//		item_value(keytab + i));
		// Uncomment to list all Z-180 verbs to assist documentation.
		//if ((keytab[i].i_uses & (VERB | Z180)) == (VERB | Z180))
		//	printf("%-6s   $%X\n", keytab[i].i_string,
		//		item_value(keytab + i));
	}

	printf("keytab OK\n");

	return 1;
}


struct item *keyword(char *name)
{
	int  r, l, u;
	struct item *ip;

	/*
	 *  binary search
	 */
	l = 0;
	u = (sizeof keytab/sizeof keytab[0])-1;
	while (l <= u) {
		char *key;
		i = (l+u)/2;
		ip = &keytab[i];
		key = ip->i_string;
		r = ci_strcmp(name + (name[0] == '.'), key + (key[0] == '.'));
		if (r == 0) {
			// Do not allow ".foo" to match "foo"
			if (name[0] == '.' && key[0] != '.')
				break;

			return ip;
		}
		if (r < 0)
			u = i-1;
		else
			l = i+1;
	}

	// Check if there's an alias.
	ip = locate(name);
	if (ip && (ip->i_scope & SCOPE_ALIAS))
		return keytab + ip->i_value;

	return 0;
}

int keyword_index(struct item *k)
{
	return k - keytab;
}

// Find 'name' in an item table.  Returns an empty slot if not found.
// Uses case-independent comparisions which are largely wasted as
// there is only 1 case where 'name' has not already been lowercased.

struct item *item_lookup(char *name, struct item *table, int table_size)
{
	struct item *ip;
	/*
	 *  hash into item table
	 */
	unsigned long hash = 0;
	char *p = name;
	while (*p) {
		char ch = *p++;
		if (ch >= 'A' && ch <= 'Z') ch += 'a' - 'A';
		hash += hash * 67 + ch - 113;
	}
	hash %= table_size;
	ip = &table[hash];

	for (;;) {
		if (ip->i_token == 0)
			break;
		if (ci_strcmp(name, ip->i_string) == 0)
			break;
		if (++ip >= table + table_size)
			ip = table;
	}

	return ip;
}

struct item *locate(char *name)
{
	return item_lookup(name, itemtab, ITEMTABLESIZE);
}

// Return the longest token that matches the start of the given name.
// Currently used for MRAS which will substitute macro parameters inside
// identifiers.
struct item *item_substr_lookup(char *name, int token, struct item *table, int table_size)
{
	struct item *ip = 0;
	int i;

	for (i = 0; i < table_size; i++) {
		unsigned int len;

		if (table[i].i_token != token)
			continue;

		len = strlen(table[i].i_string);
		if (ci_strcompare(name, table[i].i_string, len) == 0) {
			if (!ip || len > strlen(ip->i_string)) {
				ip = table + i;
			}
		}
	}

	return ip;
}

/*
 *  return the token associated with the string pointed to by
 *  tempbuf.  if no token is associated with the string, associate
 *  deftoken with the string and return deftoken.
 *  in either case, cause yylval to point to the relevant
 *  symbol table entry.
 *
 *  Only keys not matching the keyexclude will be returned allowing
 *  context-dependent tokenization.  Unless they match keyinclude.
 */

int tokenofitem(int deftoken, int keyexclude, int keyinclude)
{
	struct item *ip;
	int  i;

#ifdef T_DEBUG
	fputs("'tokenofitem entry'	", stderr) ;
	fputs(tempbuf, stderr) ;
#endif

	// Allow macros to override built-ins
	// Maybe shouldn't be done for identifiers that will undergo
	// '.' and '_' expansion.
	ip = locate(tempbuf);
	if (ip->i_token == MNAME)
		goto found;

	if (full_exprs)
		keyexclude = ~TERM;

	ip = keyword(tempbuf);
	if (ip) {
		if (ip->i_uses & keyinclude)
			goto found;

		if (!(ip->i_uses & keyexclude))
			goto found;
	}

	// This is really my own thing rather than old zmac, but zmac
	// didn't support it and it does depend on '$' crushing a bit.
	// I (ABlobOfGarbage, different person) quickly patched this 
	// together so that i could have local labels without having 
	// to enable all of zcompat. 
	// It is a bit ugly and messy, but that is because i didn't 
	// want to change the existing features.
	if (zcompat || dot_locals || file_locals) {
	    // '_' prefixed labels are local to the file
	    if (tempbuf[0] == '_' && (zcompat || file_locals)) {
		    strcat(tempbuf, "$");
		    strcat(tempbuf, basename(src_name[now_in]));
	    }

	    // '.' prefixed labels are local between labels
	    if (tempbuf[0] == '.' && (zcompat || dot_locals)) {
		    char *p = tempbuf;
		    while (*p) p++;
		    sprintf(p, "$%d", llseq);
	    }
	}

	ip = locate(tempbuf);

	if (ip->i_token)
		goto found;

	if (!deftoken) {
		i = 0 ;
		goto token_done ;
	}
	if (++nitems > ITEMTABLESIZE-20)
		error("item table overflow");
	ip->i_string = malloc(strlen(tempbuf)+1);
	ip->i_token = deftoken;
	ip->i_uses = 0;
	strcpy(ip->i_string, tempbuf);

found:
	if (*ifptr) {
		if (ip->i_token == ENDIF_TK) {
			i = ENDIF_TK;
			goto token_done ;
		}
		if (ip->i_token == ELSE_TK) {
			/* We must only honour the ELSE if it is not
			   in a nested failed IF/ELSE */
			char forbid = 0;
			char *ifstackptr;
			for (ifstackptr = ifstack; ifstackptr != ifptr; ++ifstackptr) {
				if (*ifstackptr) {
					forbid = 1;
					break;
				}
			}
			if (!forbid) {
				i = ELSE_TK;
				goto token_done;
			}
		}
		if (ip->i_token == IF_TK || ip->i_token == IF_DEF_TK ||
			ip->i_token == IF_CP_TK)
		{
			if (ifptr >= ifstmax)
				error("Too many ifs");
			else *++ifptr = 1;
		}
		i = skipline(' ');
		goto token_done ;
	}
	yylval.itemptr = ip;
	i = ip->i_token;
token_done:
#ifdef T_DEBUG
	fputs("\t'tokenofitem exit'\n", stderr) ;
#endif
	return(i) ;
}

void itemcpy(struct item *dst, struct item *src)
{
	if (dst && src && dst != src) {
		dst->i_string = src->i_string;
		dst->i_value = src->i_value;
		dst->i_token = src->i_token;
		dst->i_uses = src->i_uses;
		dst->i_scope = src->i_scope;
		dst->i_chain = src->i_chain;
		dst->i_pass = src->i_pass;
	}
}

/*
 *  interchange two entries in the item table -- used by custom_qsort
 */
void interchange(int i, int j)
{
	struct item temp;

	itemcpy(&temp, itemtab + i);
	itemcpy(itemtab + i, itemtab + j);
	itemcpy(itemtab + j, &temp);
}



/*
 *  quick sort -- used by compactsymtab to sort the symbol table
 */
void custom_qsort(int m, int n)
{
	int  i, j;

	if (m < n) {
		i = m;
		j = n+1;
		for (;;) {
			do i++; while(strcmp(itemtab[i].i_string,
					itemtab[m].i_string) < 0);
			do j--; while(strcmp(itemtab[j].i_string,
					itemtab[m].i_string) > 0);
			if (i < j) interchange(i, j); else break;
		}
		interchange(m, j);
		custom_qsort(m, j-1);
		custom_qsort(j+1, n);
	}
}

int getcol()
{
	return inpptr - inpbuf;
}

void dri_setmacro(int op) {
	if (op == '-') {
		mopt = 0;
	} else if (op == '+') {
		mopt = 1;
	} else { // '*'
		mopt = 2;
	}
}

int mc_quote;
int mc_first;

void start_multi_check()
{
	mc_quote = -1;
	mc_first = 1;
}

int found_multi(int ch)
{

	if (ch == mc_quote && (mc_quote == '"' || mc_quote == '\''))
		mc_quote = -1;
	else if (mc_quote < 0 && (ch == '\'' || ch == '"' || ch == ';'))
		mc_quote = ch;
	else if (ch == '*' && mc_first)
		mc_quote = '*';

	mc_first = 0;
	if (ch == separator && mc_quote < 0)
		return 1;

	return 0;
}

/*
 *  get the next character
 */
int nextchar()
{
	int c, ch;
	unsigned char *p;
	char *getlocal();

	if (peekc != NOPEEK) {
		c = peekc;
		peekc = NOPEEK;
		return c;
	}

	if (inpptr) {
		int col = getcol();

		// Double nul indicates EOF for macros
		if (expptr && inpptr[0] == '\0' && inpptr[1] == '\0') {
			inpptr = 0;
			return 0;
		}

		if (col == 0) {
			void analyze_inpbuf(void);
			void mras_operator_separate(void);

			if (driopt && inpptr[0] == '*') {
				addtoline(*inpptr++);
				c = skipline(inpptr[0]);
				linein[now_in]++;
				return c;
			}

			if (!expptr && !prev_multiline)
				linein[now_in]++;

			analyze_inpbuf();

			// TODO - I think this code and comnt is unnecessary
			if (driopt && comnt) {
				addtoline(*inpptr++);
				c = skipline(*inpptr);
				linein[now_in]++;
				return c;
			}

			if (macopt) {
				dri_setmacro(macopt);
				addtoline(*inpptr++);
				c = skipline(inpptr[0]);
				linein[now_in]++;
				macopt = 0;
				return c;
			}

			if (mras)
				mras_operator_separate();
		}

		if (inpbuf_insert[col]) {
			c = inpbuf_insert[col];
			inpbuf_insert[col] = '\0';
		}
		else {
			c = *inpptr++;
			addtoline(c);
		}

		if (*inpptr == '\0')
			inpptr = 0;

		return c;
	}

	inpptr = inpbuf;
	logcol = 0;
	p = inpbuf;

	// XXX - should check for input line overflow!

	// If invoking a macro then pull the next line from it.
	if (expptr) {
		start_multi_check();
		for (;;) {
			ch = getm();

			if (ch == '\1') { /* expand argument */
				ch = getm() - 'A';
				if (ch >= 0 && ch < PARMMAX && est[ch].param) {
					strcpy((char *)p, est[ch].param);
					p = (unsigned char *)strchr((char *)p, '\0');
				}
			}
			else if (ch == '\2') {	/*  local symbol  */
				ch = getm() - 'A';
				if (ch >= 0 && ch < PARMMAX && est[ch].param)
					strcpy((char *)p, est[ch].param);
				else
					strcpy((char *)p, getlocal(ch, est[TEMPNUM].value));

				p = (unsigned char *)strchr((char *)p, '\0');
			}
			else if (ch == '\3') { // Number of arguments
				sprintf((char *)p, "%d", est[MNUMPAR].value);
				p = (unsigned char *)strchr((char *)p, '\0');
			}
			else {
				if (ch == 0)
					break;

				*p++ = ch;

				if (ch == '\n')
					break;

				if (found_multi(ch)) {
					p[-1] = '\n';
					multiline = 1;
					break;
				}
			}
		}
		*p = '\0';
		p[1] = ch;
	}
	else {
		start_multi_check();

		for (;;) {
			ch = nextline_peek != NOPEEK ? nextline_peek : getc(now_file);
			nextline_peek = NOPEEK;

			if (ch == '\r') {
				nextline_peek = getc(now_file);
				if (nextline_peek == '\n')
					nextline_peek = NOPEEK;

				ch = '\n';
			}

			if (ch == EOF)
				break;

			*p++ = ch;

			if (ch == '\n') 
				break;

			if (found_multi(ch) && !inmlex) {
				p[-1] = '\n';
				multiline = 1;
				break;
			}
		}

		*p = '\0';

		/* if EOF, check for include file */
		if (ch == EOF) {
			if (now_in) {
				fclose(fin[now_in]) ;
				free(src_name[now_in]);
				now_file = fin[--now_in];
				nextline_peek = linepeek[now_in];
			}
			else if (p == inpbuf)
				return 0;
	
			if (linein[now_in] < 0) {
				lstoff = 1;
				linein[now_in] = -linein[now_in];
			} else {
				lstoff = 0 ;
			}

			if (outpass) {
				if (iflist()) {
					lineout();
					fprintf(fout, "**** %s ****\n", src_name[now_in]) ;
				}
				if (fbds)
					fprintf(fbds, "%04x %04x f %s\n", dollarsign, emit_addr, src_name[now_in]);
			}

			if (p != inpbuf) {
				*p++='\n';
				*p = '\0';
			}
			else
				inpptr = 0;
		}
	}

	return nextchar();
}

char *skipspace(char *p)
{
	while (CHARCLASS(*p) == SPACE)
		p++;

	return p;
}

// Look at inpbuf and try to determine what logical column we are starting
// at.  We could put all of the work in here and keep yylex simple but for
// now we share the load.

void analyze_inpbuf(void)
{
	int cc;
	char *p, *q, save;
	char *word1, *word2;
	struct item *ip, *word1item;
	int triplecase = 1;

	macopt = 0;

	// No need to do this when pulling in data for a macro.  In fact,
	// in can be harmful to undef a macro.
	if (inmlex)
		return;

	// Default if we find nothing to override
	logcol = 0;

	// One case to check is when you start with whitespace yet there are
	// 3 columns.  If so then we change logcol to -1 to compensate.
	// If the 2nd column is a VERB.

	// If we start with whitespace then we can give up on triple word case.
	p = (char *)inpbuf;
	if (CHARCLASS(*p) != SPACE)
		triplecase = 0;

	p = skipspace(p);
	word1 = p;

	// Special comment if first non-space char is '*'
	if (driopt) {
		comnt = (*p == '*');
		if (comnt)
			return;
	}

	// Now skip over a token or abort if we don't find one

	cc = CHARCLASS(*p);
	if (cc != LETTER && cc != STARTER && cc != DIGIT && cc != DOLLAR)
		return;

	if (driopt && *p == '$' && (p[1] == '-' || p[1] == '+' || p[1] == '*') &&
		strncasecmp(p + 2, "macro", 5) == 0 &&
		(p[7] == 0 || p[7] == '\n' || CHARCLASS(p[7]) == SPACE))
	{
		macopt = p[1];
	}

	for (;;) {
		cc = CHARCLASS(*p);
		if (cc == LETTER || cc == STARTER || cc == DIGIT || cc == DOLLAR)
			p++;
		else
			break;
	}

	// We could skip space-separated colons now, but if we see a colon
	// both issues have been decided to do that because it is easier.
	if (*p == ':')
		return;

	save = *p;
	*p = '\0';
	word1item = locate(word1);
	*p = save;

	p = skipspace(p);

	// Another token to skip past.
	// But we need to examine it to see if it is a verb.

	cc = CHARCLASS(*p);
	if (cc != LETTER && cc != STARTER && cc != DIGIT && cc != DOLLAR)
		return;

	q = p;
	word2 = p;
	for (;;) {
		cc = CHARCLASS(*p);
		if (cc == LETTER || cc == STARTER || cc == DIGIT || cc == DOLLAR)
			p++;
		else
			break;
	}

	// Now we have a second word we can check for the "name macro" case.
	// Unless we're skipping.
	save = *p;
	*p = '\0';
	if (ci_strcmp(word2, "macro") == 0 && word1item->i_token && !*ifptr)
		word1item->i_token = UNDECLARED;

	*p = save;

	if (!triplecase)
		return;

	// Must have space to skip over
	if (CHARCLASS(*p) != SPACE)
		return;

	// This 2nd token must be a verb.
	cc = *p;
	*p = '\0';
	ip = keyword(q);
	*p = cc;
	if (!ip || !(ip->i_uses & VERB))
		return;

	// Now skip over space.  If there's anything but a comment or end
	// of the line then we've may have 3 logical columns.
	// "ld a, 5" can throw that off, but we've done the verb check.

	p = skipspace(p);

	if (*p != ';' && *p != '\n' && *p != '\0')
		logcol--;
}

void mras_operator_separate(void)
{
	int i, sep;

	// Only do operator separation after macro expansion.
	if (inmlex)
		return;

	// Apply operator separation across the entire line.
	// We could limit this to logical columns if need be,
	// but I imagine MRAS didn't allow "x.mod.y" as a label
	// or macro name.

	// Strings are handled in a simple but largly compatible way.
	// AF' is a problem which can be safely ignored since its appearance
	// will mean no expression is present.
	// My allowed salting of ' after identifiers is another matter.
	// But, again, original MRAS code won't do that.

	memset(inpbuf_insert, 0, strlen((char *)inpbuf));

	sep = '\0';
	for (i = 0; inpbuf[i]; i++) {
		int j;

		if (inpbuf[i] == sep) {
			sep = '\0';
			continue;
		}

		if (inpbuf[i] == '\'' || inpbuf[i] == '"')
			sep = inpbuf[i];

		// Don't do anthing if inside a string constant.
		if (sep)
			continue;

		if (inpbuf[i] == ';')
			break;

		// Slight nod to efficiency.  Assumption is tested in
		// check_keytab().

		if (inpbuf[i] != '.')
			continue;

		for (j = 0; j < sizeof(keytab) / sizeof(keytab[0]); j++) {
			char *p = keytab[j].i_string;
			int len = strlen(p);

			if (!(keytab[j].i_uses & MRASOP))
				continue;

			if (ci_strcompare((char *)inpbuf + i, p, len) == 0) {
				// Only need to add spaces if we're possibly
				// in an identifier.  But no harm if we're not.
				inpbuf_insert[i] = ' ';
				inpbuf_insert[i + len] = ' ';
				i += len - 1;
				break;
			}
		}
	}
}


/*
 *  skip to rest of the line -- comments and if skipped lines
 */
int skipline(int ac)
{
	int  c;

	c = ac;
	while (c != '\n' && c != '\0')
		c = nextchar();
	return('\n');
}

void add_incpath(char *dir)
{
	if (incpath_cnt >= MAXINCPATH) {
		fprintf(stderr, "Sorry, can only handle %d include paths\n", MAXINCPATH);
		exit(1);
	}

	incpath[incpath_cnt++] = strdup(dir);
}

FILE *open_incpath(char *filename, char *mode, char **path_used)
{
	char quote;
	int i;
	char path[1024];
	FILE *fp;

	// Due to the way parsing works the string can be specified
	// without quotes or will allow quotes but include them.  Instead
	// of fooling with the parsing I just strip the quotes.  I think
	// you can still include a file that starts with a single or double
	// quote by quoting it, but that's an awful thing to do to yourself.

	quote = *filename;
	if (quote == '"' || quote == '\'') {
		char *p;
		for (p = filename; *p; p++)
			p[0] = p[1];

		if (p[-2] == quote)
			p[-2] = '\0';
	}

	// First look for included file in same directory as source file.

	strcpy(path, src_name[now_in]);
	*basename(path) = '\0';
	strcat(path, filename);
	fp = fopen(path, mode);
	if (fp) {
		if (path_used)
			*path_used = strdup(path);

		if (note_depend && outpass)
			printf("%s\n", path);
		return fp;
	}

	for (i = 0; i < incpath_cnt; i++) {
		sprintf(path, "%s/%s", incpath[i], filename);
		fp = fopen(path, mode);
		if (fp) {
			if (path_used)
				*path_used = strdup(path);
			if (note_depend && outpass)
				printf("%s\n", path);
			return fp;
		}
	}

	if (note_depend && outpass)
		printf("%s\n", filename);

	fp = fopen(filename, mode);
	if (fp && path_used)
		*path_used = strdup(filename);

	return fp;
}

void version()
{
	fprintf(stderr, "zmac version " VERSION "        http://48k.ca/zmac.html\n");
}

//
// Print out a usage message and exit.
//
void usage(char *msg, char *param)
{
	fprintf(stderr, msg, param);
	fprintf(stderr, "\n");
	version();
	fprintf(stderr, "usage: zmac [-8bcefghijJlLmnopstz] [-I dir] [-Pk=n] [-Dsym] file[.z]\n");
	fprintf(stderr, "other opts: --rel[7] --mras --zmac --dri --nmnv --z180 --fcal --dep --help --doc --version\n");
	fprintf(stderr, "  zmac -h for more detail about options.\n");
	exit(1);
}

void help()
{
	version();

	fprintf(stderr, "   --version\tshow version number\n");
	fprintf(stderr, "   --help\tshow this help message\n");
	fprintf(stderr, "   -8\t\tuse 8080 timings and interpretation of mnemonics\n");
	fprintf(stderr, "   -b\t\tno binary (.hex,.cmd,.cas, etc.) output\n");
	fprintf(stderr, "   -c\t\tno cycle counts in listing\n");
	fprintf(stderr, "   -e\t\terror list only\n");
	fprintf(stderr, "   -f\t\tprint if skipped lines\n");
	fprintf(stderr, "   -g\t\tdo not list extra code\n");
	fprintf(stderr, "   -h\t\tshow this information about options and quit\n");
	fprintf(stderr, "   -i\t\tdo not list include files\n");
	fprintf(stderr, "   -I dir\tadd 'dir' to include file search path\n");
	fprintf(stderr, "   -j\t\tpromote relative jumps to absolute as needed\n");
	fprintf(stderr, "   -J\t\twarn when a jump could be relative\n");
	fprintf(stderr, "   -l\t\tlist to standard output\n");
	fprintf(stderr, "   -L\t\tforce listing of everything\n");
	fprintf(stderr, "   -m\t\tprint macro expansions\n");
	fprintf(stderr, "   -n\t\tput line numbers off\n");
	fprintf(stderr, "   -o file.hex\toutput only named file (multiple -o allowed)\n");
	fprintf(stderr, "   -p\t\tput out four \\n's for eject\n");
	fprintf(stderr, "   -P\t\tformat listing for a printer\n");
	fprintf(stderr, "   -s\t\tdon't produce a symbol list\n");
	fprintf(stderr, "   -t\t\toutput error count instead of list of errors\n");
	fprintf(stderr, "   -z\t\tuse Z-80 timings and interpretation of mnemonics\n");
	fprintf(stderr, "   -Pk=num\tset @@k to num before assembly (e.g., -P4=10)\n");
	fprintf(stderr, "   -Dsym\tset symbol sym to 1 before assembly (e.g., define it)\n");
	fprintf(stderr, "   --od\tdir\tdirectory unnamed output files (default \"zout\")\n");
	fprintf(stderr, "   --oo\thex,cmd\toutput only listed file suffix types\n");
	fprintf(stderr, "   --xo\tlst,cas\tdo not output listed file suffix types\n");
	fprintf(stderr, "   --nmnv\tdo not interpret mnemonics as values in expressions\n");
	fprintf(stderr, "   --z180\tuse Z-180 timings and extended instructions\n");
	fprintf(stderr, "   --dep\tlist files included\n");
	fprintf(stderr, "   --mras\tlimited MRAS/EDAS compatibility\n");
	fprintf(stderr, "   --rel\toutput .rel file only (--rel7 for 7 character symbol names)\n");
	fprintf(stderr, "   --zmac\tcompatibility with original zmac\n");
	fprintf(stderr, "   --fcal\tidentifier in first column is always a label\n");
	fprintf(stderr, "   --doc\toutput documentation as HTML file\n");
	fprintf(stderr, "   --dotlocals\tmake labels that start with '.' local between labels\n");
	fprintf(stderr, "   --filelocals\tmake labels that start with '_' local to the file it is in\n");

	exit(0);
}

int main(int argc, char *argv[])
{
	struct item *ip;
	int  i, j;
	int  files;
	int used_o;
	int used_oo;
	char *zmac_args_env;
#ifdef DBUG
	extern  yydebug;
#endif

	separator = '\\';

	fin[0] = stdin;
	now_file = stdin;
	files = 0;
	used_o = 0;
	used_oo = 0;

	// Special flag for unit testing.
	if (argc > 1 && strcmp(argv[1], "--test") == 0)
		exit(!check_keytab());

	// To avoid typing typical command-line arguments every time we
	// allow ZMAC_ARGS environment variable to augment the command-line.
	zmac_args_env = getenv("ZMAC_ARGS");
	if (zmac_args_env) {
		int new_argc = 0;
		char *arg;
		char **new_argv;
		static char *zmac_args;

		// Overestimate to size of new argv vector.
		new_argv = malloc((argc + strlen(zmac_args_env) + 1) *
			sizeof *new_argv);
		// Save a copy because we (1) mutate it and (2) use it in argv.
		zmac_args = strdup(zmac_args_env);

		if (!new_argv || !zmac_args)
			error("malloc to support ZMAC_ARGS failed");

		memcpy(new_argv, argv, sizeof(*new_argv) * argc);
		new_argc = argc;

		arg = strtok(zmac_args, " \t");
		while (arg != NULL) {
			new_argv[new_argc++] = arg;
			arg = strtok(NULL, " \t");
		}

		argv = new_argv;
		argc = new_argc;
	}

	for (i=1; i<argc; i++) {
		int skip = 0;
		if (strcmp(argv[i], "--mras") == 0) {
			mras = 1;
			trueval = -1;
			continue;
		}

		if (strcmp(argv[i], "--dri") == 0) {
			driopt = 1;
			separator = '!';
			continue;
		}

		if (strcmp(argv[i], "--rel") == 0) {
			relopt = 6;
			continue;
		}

		if (strcmp(argv[i], "--rel7") == 0) {
			relopt = 7;
			continue;
		}

		if (strcmp(argv[i], "--zmac") == 0) {
			zcompat = 1;
			continue;
		}

		if (strcmp(argv[i], "--dotlocals") == 0) {
			dot_locals = 1;
			continue;
		}

		if (strcmp(argv[i], "--filelocals") == 0) {
			file_locals = 1;
			continue;
		}

		if (strcmp(argv[i], "--dep") == 0) {
			note_depend = 1;
			continue;
		}

		if (strcmp(argv[i], "--nmnv") == 0) {
			nmnvopt = 1;
			continue;
		}

		if (strcmp(argv[i], "--fcal") == 0) {
			first_always_label = 1;
			continue;
		}

		if (strcmp(argv[i], "--help") == 0) {
			help();
			continue;
		}

		if (strcmp(argv[i], "--doc") == 0) {
			extern void doc(int pass);
			doc(-1);
			exit(0);
			continue; // not reached
		}

		if (strcmp(argv[i], "--version") == 0) {
			version();
			exit(0);
			continue; // not reached
		}

		if (strcmp(argv[i], "--z180") == 0) {
			/* Equivalent to .z180 */
			default_z80 = 2;
			continue;
		}

		// Silently accept this option to make private unit tests happy.
		if (strcmp(argv[i], "--flow") == 0) {
			/*default_flow_warn = */ atoi(argv[i = getoptarg(argc, argv, i)]);
			continue;
		}

		if (strcmp(argv[i], "--od") == 0) {
			output_dir = argv[i = getoptarg(argc, argv, i)];
			continue;
		}

		if (strcmp(argv[i], "--oo") == 0) {
			if (!used_oo)
				stop_all_outf();

			suffix_list(argv[i = getoptarg(argc, argv, i)], 0);

			used_oo = 1;
			continue;
		}

		if (strcmp(argv[i], "--xo") == 0) {
			suffix_list(argv[i = getoptarg(argc, argv, i)], 1);
			continue;
		}

		if (argv[i][0] == '-' && argv[i][1] == '-')
			usage("Unknown option: %s", argv[i]);

		if (argv[i][0] == '-' && argv[i][1] == 'P' &&
			argv[i][2] >= '0' && argv[i][2] <= '9')
		{
			if (argv[i][3] == '=') {
				int overflow;
				int radix;
				int sign = 1;
				char *str = argv[i] + 4;
				if (*str == '-') {
					sign = -1;
					str++;
				}

				radix = convert(str, NULL, &overflow);
				if (radix <= 0 || overflow)
					usage("bad -Pn= parameter value", 0);

				mras_param[argv[i][2] - '0'] = sign * yylval.ival;
				mras_param_set[argv[i][2] - '0'] = 1;
			}
			else if (argv[i][3] == '\0') {
				mras_param[argv[i][2] - '0'] = -1;
				mras_param_set[argv[i][2] - '0'] = 1;
			}
			else
				usage("-Pn syntax error", 0);

			continue;
		}

		if (argv[i][0] == '-' && argv[i][1] == 'D') {
			struct cl_symbol *sym = malloc(sizeof(struct cl_symbol));
			if (!argv[i][2])
				usage("missing symbol name for -D", 0);

			sym->name = argv[i] + 2;
			sym->next = cl_symbol_list;
			cl_symbol_list = sym;

			continue;
		}

		if (*argv[i] == '-') while (*++argv[i]) {
			switch(*argv[i]) {

			case '8':	/* Equivalent to .8080 */
				default_z80 = 0;
				continue;

			case 'b':	/*  no binary  */
				for (j = 0; j < CNT_OUTF; j++)
					if (strcmp(outf[j].suffix, "lst") != 0)
						outf[j].no_open = 1;
				continue;

			case 'c':	/*  no cycle counts in listing */
				copt-- ;
				continue;

#ifdef DBUG
			case 'd':	/*  debug  */
				yydebug++;
				continue;
#endif

			case 'e':	/*  error list only  */
				eopt = 0;
				edef = 0;
				continue;

			case 'f':	/*  print if skipped lines  */
				fopt++;
				fdef++;
				continue;

			case 'g':	/*  do not list extra code  */
				gopt = 0;
				gdef = 0;
				continue;

			case 'h':
				help();
				continue;

			case 'i':	/* do not list include files */
				iopt = 1 ;
				continue ;

			case 'I':
				if (argv[i][1])
					add_incpath(argv[i] + 1);
				else
					add_incpath(argv[i = getoptarg(argc, argv, i)]);
				skip = 1;
				break;

			case 'l':	/*  list to stdout */
				fout = stdout;
				continue;

			case 'L':	/*  force listing of everything */
				lston++;
				continue;

			case 'j':	// promote relative jumps to absolute as needed
				default_jopt = 1;
				continue;

			case 'J':	// error when JR instructions could replace JP
				default_JPopt = 1;
				continue;

			case 'm':	/*  print macro expansions  */
				mdef++;
				mopt++;
				continue;

			case 'n':	/*  put line numbers off */
				nopt-- ;
				continue;

			case 'o':	/*  select output */
				{
					char *outfile = 0;
					char *sfx;
					int found = 0;

					if (!used_o)
						stop_all_outf();

					if (argv[i][1])
						outfile = argv[i] + 1;
					else
						outfile = argv[i = getoptarg(argc, argv, i)];

					for (sfx = outfile; !found && *sfx; sfx++) {
						if (*sfx != '.')
							continue;

						for (j = 0; j < CNT_OUTF; j++) {
							if (ci_strcmp(sfx + 1, outf[j].suffix) == 0) {
								outf[j].no_open = 0;
								outf[j].wanted = 1;
								outf[j].filename = outfile;
								found = 1;
								break;
							}
						}
					}
					if (!found)
						usage("output file '%s' has unknown suffix", outfile);
				}
				used_o = 1;
				skip = 1;
				break;

			case 'p':	/*  put out four \n's for eject */
				popt-- ;
				continue;

			case 'P':	// GWP - printer style output (headers, page separation, etc.)
				printer_output = 1;
				continue;

			case 's':	/*  don't produce a symbol list  */
				sopt++;
				continue;

			case 't':	/*  output only number of errors */
				topt = 0;
				continue;

			case 'z':	/* Equivalent to .z80 */
				default_z80 = 1;
				continue;

			default:	/*  error  */
				{
					char badopt[2] = { argv[i][0], 0 };
					usage("Unknown option: %s", badopt);
				}
			}
			if (skip)
				break;
		}
		else if (files++ == 0) {
			sourcef = argv[i];
			strcpy(src, sourcef);
			if ((now_file = fopen(src, "r")) == NULL) {
				if (!*getsuffix(src))
					suffix(src, ".z");
				if ((now_file = fopen(src, "r")) == NULL)
					usage("Cannot open source file '%s'", src);
			}
			now_in = 0;
			fin[now_in] = now_file ;
			src_name[now_in] = src ;
		} else if (files)
			usage("Too many arguments", 0);
	}


	if (files == 0)
		usage("No source file", 0);

	// .wav file outputs must ensure their .cas antecedents are generated.
	// And also check for .rel output and set relopt while we're at it.
	for (j = 0; j < CNT_OUTF; j++) {
		char *p;

		if (strcmp(outf[j].suffix, "rel") == 0 && !outf[j].no_open && !relopt)
			relopt = 6;

		p = strchr(outf[j].suffix, '.');
		// Only .wav file that open matter and only if .cas doesn't open.
		if (!p || strcmp(p, ".wav") != 0 || outf[j].no_open || !outf[j + 1].no_open)
			continue;

		outf[j + 1].no_open = 0;
		outf[j + 1].temp = 1;
		if (outf[j].filename) {
			// Replace .wav suffix with .cas.  This is safe for
			// now as only -o can choose a filename and it must end
			// with outf[j]'s suffix to be put in outf[j].
			outf[j + 1].filename = strdup(outf[j].filename);
			p = strrchr(outf[j + 1].filename, '.');
			strcpy(p + 1, "cas");
		}
	}

	if (relopt) {
		for (j = 0; j < CNT_OUTF; j++) {
			if (strcmp(outf[j].suffix, "lst") != 0)
			{
				outf[j].no_open = strcmp(outf[j].suffix, "rel") != 0;
			}
		}
	}

	for (j = 0; j < CNT_OUTF; j++) {
		if (outf[j].no_open || *outf[j].fpp)
			continue;

		if (!outf[j].filename) {
			char suffix[32];
			strcpy(suffix, ".");
			strcat(suffix, outf[j].suffix);
			outpath(oth, sourcef, suffix);
			outf[j].filename = strdup(oth);
		}

		*outf[j].fpp = fopen(outf[j].filename, outf[j].mode);
		if (!*outf[j].fpp) {
			fprintf(stderr, "Cannot create file '%s'", outf[j].filename);
			clean_outf();
			exit(1);
		}
	}

	if (fbds) {
		fprintf(fbds, "binary-debuggable-source\n");
		fprintf(fbds, "%04x %04x f %s\n", dollarsign, emit_addr, src_name[now_in]);
	}

	// Tape header
	for (i = 0; i < 255; i++) {
		if (flcas) fputc(0, flcas);
		if (flnwcas) fputc(0, flnwcas);
		if (fcas) fputc(0x55, fcas);
		if (ftcas) fputc(0, ftcas);
	}
	if (flcas) fputc(0xA5, flcas);
	if (flnwcas) fputc(0xA5, flnwcas);
	if (fcas) fputc(0x7F, fcas);
	if (ftcas) fputc(0xA5, ftcas);

	casname(oth, sourcef, 6);
	putcas(0x55);
	for (i = 0; i < 6; i++)
		putcas(oth[i]);

	if (relopt) {
		strncpy(progname, basename(sourcef), sizeof progname);
		progname[sizeof progname - 1] = '\0';
	}

	// mfopen() is always in-memory not a temporary file.

	mfile = mfopen("does-not-matter","w+b") ;

	/*
	 *  get the time
	 */
	time(&now);
	timp = ctime(&now);
	timp[16] = 0;
	timp[24] = 0;

	title = sourcef;
	/*
	 * pass 1
	 */
#ifdef DEBUG
	fputs("DEBUG-pass 1\n", stderr) ;
#endif
	clear();
	setvars();
	npass = 1;
	outpass = 0;
	yyparse();

	// GWP - errors should stop us, but the listing is very useful.

	pass2++;

	for (npass = 2; npass < MAXPASS; npass++) {
		if (passfail || npass == MAXPASS - 1)
			outpass = 1;

		if (outpass) {
			putrelcmd(RELCMD_PROGNAME);
			putrelname(progname);
		}

		for (ip = itemtab - 1; ++ip < itemmax; ) {
			// Output list of public labels.  m80 will let
			// equates and aseg values be public so we do, too.
			if (outpass && ip->i_token && (ip->i_scope & SCOPE_PUBLIC)) {
				putrelcmd(RELCMD_PUBLIC);
				putrelname(ip->i_string);
			}

			/* reset use count */
			ip->i_uses = 0 ;

			/* set macro names, equated and defined names */
			switch	(ip->i_token) {
			case MNAME:
				ip->i_token = UNDECLARED;
				break;

			case EQUATED:
				ip->i_token = WASEQUATED;
				break;

			case DEFLED:
				if (zcompat)
					ip->i_token = UNDECLARED;
				break;
			}
		}

		if (outpass) {
			// m80 outputs data size as an absolute value, but
			// code size as code segment relative.  Odd, but
			// I'll follow suit.
			putrelcmd(RELCMD_DATASIZE);
			putrelsegref(SEG_ABS, seg_size[SEG_DATA]);

			putrelcmd(RELCMD_CODESIZE);
			putrelsegref(SEG_CODE, seg_size[SEG_CODE]);
		}

		for (ip = itemtab - 1; ++ip < itemmax; ) {
			if (ip->i_token != COMMON)
				continue;

			// TODO: perhaps have WASCOMMON but this will suffice
			ip->i_token = UNDECLARED;

			putrelcmd(RELCMD_COMSIZE);
			putrelsegref(SEG_ABS, ip->i_value);
			putrelname(ip->i_string);
		}

		// In case we hit 'end' inside an included file
		while (now_in > 0) {
			fclose(fin[now_in]);
			free(src_name[now_in]);
			now_file = fin[--now_in];
			nextline_peek = linepeek[now_in];
		}
		setvars();
		clear_instdata_flags();
		fseek(now_file, (long)0, 0);

	#ifdef DEBUG
		fprintf(stderr, "DEBUG- pass %d\n", npass) ;
	#endif

		yyparse();

		if (outpass || passfail)
			break;

		if (!passretry)
			outpass = 1;
	}

	flushbin();
	flushoth();

	if (fbuf)
		putc(':', fbuf);

	if (xeq_flag) {
		if (fbuf) {
			puthex(0, fbuf);
			puthex(xeq >> 8, fbuf);
			puthex(xeq, fbuf);
			puthex(1, fbuf);
			puthex(255-(xeq >> 8)-xeq, fbuf);
		}
		if (fcmd) {
			fprintf(fcmd, "%c%c%c%c", 2, 2, xeq, xeq >> 8);
			fflush(fcmd);
		}
		putcas(0x78);
		putcas(xeq);
		putcas(xeq >> 8);
		if (fmds)
			fprintf(fmds, "pc=$%04x\ng\n", xeq);
	}
	else {
		// SYSTEM cassette files must have an execution address.
		// Without one we simply do not output .cas or .wav SYSTEM.

		int i;
		for (i = 0; i < CNT_OUTF; i++) {
			if (*outf[i].fpp && outf[i].system) {
				fclose(*outf[i].fpp);
				*outf[i].fpp = NULL;
				// unlink is an intended implicit declaration -- silence the gcc warning.
				// Old gcc's don't permit #pragman in a function.
				// Uncomment to suppress the warning.
				//#pragma GCC diagnostic push
				//#pragma GCC diagnostic ignored "-Wimplicit-function-declaration"
				unlink(outf[i].filename);
				//#pragma GCC diagnostic pop
				if (outf[i].wanted)
					fprintf(stderr, "Warning: %s not output -- no entry address (forgot \"end label\")\n", outf[i].filename);
			}
		}

		if (fbuf) {
			puthex(0, fbuf);
			puthex(0, fbuf);
			puthex(0, fbuf);
			puthex(1, fbuf);
			puthex(255, fbuf);
		}
	}

	if (fbuf) {
		putc('\n', fbuf);
		fflush(fbuf);
	}

	padcas();

	if (relopt) {
		struct item *ip;
		// Output external symbols and value of public symbols
		for (ip = itemtab; ip < itemmax; ip++) {
			if (ip->i_token == UNDECLARED && (ip->i_scope & SCOPE_EXTERNAL)) {
				putrelcmd(RELCMD_EXTCHAIN);
				// Chain value will have top two bits set appropriately
				putrelextaddr(ip->i_chain);
				putrelname(ip->i_string);
			}
			if (ip->i_scope & SCOPE_PUBLIC)
			{
				putrelcmd(RELCMD_PUBVALUE);
				putrelsegref(ip->i_scope, ip->i_value);
				putrelname(ip->i_string);
			}
		}

		// End module, entry address if any
		putrelcmd(RELCMD_ENDMOD);
		putrelextaddr(rel_main);
		flushrel(); // byte alignment expected after end module

		// End .rel file
		putrelcmd(RELCMD_ENDPROG);
		flushrel();
	}

	if (xeq_flag == 0) {
#if WIN32
		char *username = getenv("USERNAME");
		if (username && strcmp(username, "George") == 0 && !relopt) {
			CONSOLE_SCREEN_BUFFER_INFO inf;
			HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			GetConsoleScreenBufferInfo(hOut, &inf);
			SetConsoleTextAttribute(hOut, FOREGROUND_RED|FOREGROUND_GREEN|FOREGROUND_INTENSITY);
			fprintf(stderr, "Warning: no entry address (forgot \"end label\")\n");
			fflush(stderr);
			SetConsoleTextAttribute(hOut, inf.wAttributes);
		}
#endif
	}
	else if (fbds) {
		fprintf(fbds, "%04x e\n", xeq);
	}

	if (fcim || fams || ftap || ftcas) {
		int low = 0;
		int high = sizeof(memory) - 1;
		int chk;
		int filelen;
		int i;
		char leafname[] = "FILENAMEBIN";

		while (low < sizeof(memory) && (memflag[low] & (MEM_INST | MEM_DATA)) == 0)
			low++;

		while (high >= 0 && (memflag[high] & (MEM_INST | MEM_DATA)) == 0)
			high--;

		if (high >= low && fcim)
			fwrite(memory + low, high + 1 - low, 1, fcim);

		filelen = (high + 1) - low;

		// AMSDOS binary file output (A for Amstrad, code from zmac 1.3)
		if (fams) {
			chk = 0;
			putc(0, fams);
			for (i = 0; i < 11; i++) {
				putc(leafname[i], fams);
				chk += leafname[i];
			}
			for (i = 0; i < 6; i++)
				putc(0, fams);

			putc(2, fams); // Unprotected binary
			chk += 2;
			putc(0, fams);
			putc(0, fams);
			putc(low & 0xff, fams);
			chk += low & 0xff;
			putc(low >> 8, fams);
			chk += low >> 8;
			putc(0, fams);
			putc(filelen & 0xff, fams);
			chk += filelen & 0xff;
			putc(filelen >> 8, fams);
			chk += filelen >> 8;
			putc(xeq & 0xff, fams);
			chk += xeq & 0xff;
			putc(xeq >> 8, fams);
			chk += xeq >> 8;
			for (i = 28; i < 64; i++)
				putc(0, fams);

			putc(filelen & 0xff, fams);
			chk += filelen & 0xff;
			putc(filelen >> 8, fams);
			chk += filelen >> 8;
			putc(0, fams); // this would be used if filelen > 64K
			putc(chk & 0xff, fams);
			putc(chk >> 8, fams);

			for (i = 69; i < 128; i++)
				putc(0, fams);

			if (filelen > 0)
				fwrite(memory + low, filelen, 1, fams);

			if (filelen & 0x7f)
				putc(0x1a, fams); // CP/M EOF character
		}

		if (ftap)
			write_tap(filelen, low, memory + low);
 
		if (ftcas)
			write_250(low, high);
	}

	// Output .wav files noting the padding bits to ignore.
	writewavs(0, cas_low_pad, cas_high_pad);

	if (fbds) {
		struct item *tp;

		for (tp = itemtab; tp < itemmax; tp++) {
			if (tp->i_token == LABEL)
				fprintf(fbds, "%04x a %s\n", tp->i_value, tp->i_string);
			else if (tp->i_token == EQUATED)
				fprintf(fbds, "%04x v %s\n", tp->i_value, tp->i_string);
		}
	}

	if (fout)
		fflush(fout);
	if (writesyms)
		outsymtab(writesyms);
	compactsymtab();
	if (eopt)
		erreport();
	if (!sopt)
		putsymtab();
	if (fout) {
		eject();
		fflush(fout);
	}
	// GWP - some things (like balance errors in macro definitions) do
	// not show up until you use them.  So just in case we print an error
	// count here as not to confuse the programmer who is unlikely to check
	// the listing for errors if none are shown in the command window.
	if (counterr() > 0)
		fprintf(stderr, "%d errors (see listing if no diagnostics appeared here)\n", counterr());
	if (countwarn() > 0)
		fprintf(stderr, "%d warnings (see listing if no diagnostics appeared here)\n", countwarn());

	clean_outf_temp();
	if (counterr() > 0)
		clean_outf();
	exit(counterr() > 0);
}

int getoptarg(int argc, char *argv[], int i)
{
	i++;
	if (i < argc)
		return i;

	usage("missing argument for %s option", argv[i - 1]);
	return i; // not actually reached
}

void stop_all_outf()
{
	int i;
	for (i = 0; i < CNT_OUTF; i++)
		outf[i].no_open = 1;
}

void clean_outf()
{
	int i;

	for (i = 0; i < CNT_OUTF; i++) {
		if (*outf[i].fpp) {
			int size = ftell(*outf[i].fpp);
			fclose(*outf[i].fpp);
			*outf[i].fpp = NULL;
			// Listing file can stick around, but not if empty.
			if (strcmp(outf[i].suffix, "lst") != 0 || size == 0)
				unlink(outf[i].filename);
		}
	}
}

void clean_outf_temp()
{
	int i;
	for (i = 0; i < CNT_OUTF; i++) {
		if (*outf[i].fpp && outf[i].temp) {
			fclose(*outf[i].fpp);
			*outf[i].fpp = NULL;
			unlink(outf[i].filename);
		}
	}
}

// Set output files to open or not using a comma-separated list of suffixes.
// Loops over the outf[] suffix so that "wav" can be used to eliminate all
// .wav files.
void suffix_list(char *sfx_lst, int no_open)
{
	while (sfx_lst) {
		int i;
		char *p = strchr(sfx_lst, ',');
		if (p)
			*p = '\0';

		// Allow prefix '.' in case user puts them in.
		while (*sfx_lst == '.')
			sfx_lst++;

		for (i = 0; i < CNT_OUTF; i++) {
			char *sfx;
			for (sfx = outf[i].suffix; sfx; ) {
				if (ci_strcmp(sfx, sfx_lst) == 0) {
					outf[i].no_open = no_open;
					if (!no_open)
						outf[i].wanted = 1;
				}
				sfx = strchr(sfx, '.');
				if (sfx)
					sfx++;
			}
		}

		sfx_lst = p ? p + 1 : 0;
	}
}

void equate(char *id, int value, int scope)
{
	struct item *it;

	it = locate(id);
	if (!it->i_token) {
		nitems++;
		it->i_value = value;
		it->i_token = EQUATED;
		it->i_pass = npass;
		it->i_scope = scope;
		it->i_uses = 0;
		it->i_string = malloc(strlen(id)+1);
		strcpy(it->i_string, id);
	}

	// This variable test true for ifdef
	// This is a slightly subtle way to ensure it->i_pass == npass
	// Setting it to npass or npass + 1 doesn't always work due to
	// the different contexts in which setvars() is called.
	if (scope & (SCOPE_CMD_D | SCOPE_CMD_P))
		it->i_pass++;
}

/*
 *  set some data values before each pass
 */
void setvars()
{
	int  i;
	struct cl_symbol *sym;

	peekc = NOPEEK;
	inpptr = 0;
	nextline_peek = NOPEEK;
	raw = 0;
	linein[now_in] = 0;
	exp_number = 0;
	emitptr = emitbuf;
	lineptr = linebuf;
	ifptr = ifstack;
	*ifptr = 0;
	dollarsign = 0;
	emit_addr = 0;
	olddollar = 0;
	oldothdollar = 0;
	phaseflag = 0;
	for (i=0; i<FLAGS; i++) err[i] = 0;
	tstates = 0;
	ocf = 0;
	llseq = 0;
	passfail = 0;
	passretry = 0;
	njrpromo = 0;
	jopt = default_jopt;
	JPopt = default_JPopt;
	strcpy(modstr, "@@@@");
	segment = SEG_CODE;
	cur_common = NULL;
	memset(seg_pos, 0, sizeof(seg_pos));
	memset(seg_size, 0, sizeof(seg_size));
	segchange = 0;
	z80 = default_z80;
	outrec = 0;
	outlen = 0;

	param_parse = 0;
	arg_reset();

	mfptr = 0;
	mfseek(mfile, mfptr, 0);

	// TODO - maybe these could be just as well handled lexically
	// like the 8080 opcodes in DRI mode?
	// These are slightly harmful, but not too bad.  Only
	// absolutely necessary for MAC compatibility.  But there's
	// some use in having them available always.

	equate("b", 0, SCOPE_BUILTIN);
	equate("c", 1, SCOPE_BUILTIN);
	equate("d", 2, SCOPE_BUILTIN);
	equate("e", 3, SCOPE_BUILTIN);
	equate("h", 4, SCOPE_BUILTIN);
	equate("l", 5, SCOPE_BUILTIN);
	equate("m", 6, SCOPE_BUILTIN);
	equate("a", 7, SCOPE_BUILTIN);

	equate("sp", 6, SCOPE_BUILTIN);
	equate("psw", 6, SCOPE_BUILTIN);

	// TODO - these are now handled lexically in --dri mode
	// There are a large number of symbols to add to support
	// "LXI H,MOV" and the like.

	// Technically only MRAS has these, but I'll wait and see if
	// anyone actually uses @@0 through @@9.  If so, then we can
	// DEFL them instead of EQU.
	for (i = 0; i < 10; i++) {
		char var[4];
		var[0] = '@';
		var[1] = '@';
		var[2] = '0' + i;
		var[3] = '\0';
		equate(var, mras_param[i], mras_param_set[i] ? SCOPE_CMD_P : SCOPE_BUILTIN);
	}

	for (sym = cl_symbol_list; sym; sym = sym->next)
		equate(sym->name, 1, SCOPE_CMD_D);

	reset_import();
}

//
// Clear out cycle counts and memory.
//

void clear()
{
	int i;

	for (i = 0; i < sizeof(memory) / sizeof(memory[0]); i++)
	{
		memory[i] = 0;
		memflag[i] = 0;
		tstatesum[i] = 0;
	}
}

void clear_instdata_flags()
{
	int i;

	for (i = 0; i < sizeof(memory) / sizeof(memory[0]); i++)
		memflag[i] &= ~(MEM_DATA | MEM_INST);
}

void setmem(int addr, int value, int type)
{
	value &= 0xff;
	memory[addr] = value;
	memflag[addr] |= type;
}

/*
 *  print out an error message and die
 */
void error(char *as)
{
	*linemax = 0;
	if (fout) {
		fprintf(fout, "%s\n", linebuf);
		fflush(fout);
	}
	fprintf(stderr, "%s\n", as) ;
	clean_outf();
	exit(1);
}


/*
 * Compact the symbol table, removing unused, UNDECLARED entries,
 * macros and built-in identifiers.
 */
void compactsymtab()
{
	struct item *tp, *fp;

	if (!nitems)
		return;

	tp = itemtab;
	tp--;
	for (fp = itemtab; fp<itemmax; fp++) {
		if (fp->i_token == UNDECLARED && !(fp->i_scope & SCOPE_EXTERNAL)) {
			nitems--;
			continue;
		}
		if (fp->i_token == 0)
			continue;

		// Don't list macros or internally defined symbols
		if (fp->i_token == MNAME || (fp->i_scope & SCOPE_BUILTIN)) {
			nitems--;
			continue;
		}

		tp++;
		itemcpy(tp, fp);
	}

	tp++;
	tp->i_string = "{";	/* } */

	/*  sort the table */
	custom_qsort(0, nitems-1);
}

/*
 *  output the symbol table
 */
void putsymtab()
{
	int  i, j, k, t, rows;
	char c, seg = ' '; //, c1;
	int numcol = printer_output ? 4 : 1;
	struct item *tp;

	if (!nitems || !fout)
		return;

	title = "**  Symbol Table  **";

	rows = (nitems+numcol-1) / numcol;
	if (rows+5+line > 60)
		eject();
	lineout();
	fprintf(fout,"\n\n\nSymbol Table:\n\n") ;
	line += 4;

	for (i=0; i<rows; i++) {
		for(j=0; j<numcol; j++) {
			k = rows*j+i;
			if (k < nitems) {
				tp = &itemtab[k];
				t = tp->i_token;
				c = ' ' ;
				if (t == EQUATED || t == DEFLED)
					c = '=' ;
				if (t == COMMON)
					c = '/';

				//if (tp->i_uses == 0)
				//	c1 = '+' ;
				//else
				//	c1 = ' ' ;

				// GWP - decided I don't care about uses
				// even if it were accurate.
				// TODO: Should use maxsymbol size in there,
				// but makes output harder to read.

				fprintf(fout, "%-15s%c", tp->i_string, c);

				if (tp->i_scope & SCOPE_ALIAS)
					fprintf(fout, "\"%s\"",
						keytab[tp->i_value].i_string);

				else {
					if (relopt)
						seg = SEGCHAR(tp->i_scope & SCOPE_SEGMASK);

					if (tp->i_value >> 16)
						fprintf(fout, "%08X%c", tp->i_value, seg);
					else if (tp->i_value >> 8)
						fprintf(fout, "%4X%c    ", tp->i_value, seg);
					else
						fprintf(fout, "%02X%c      ", tp->i_value, seg);

					fprintf(fout, " %d", tp->i_value);

					if (tp->i_scope & SCOPE_EXTERNAL)
						fprintf(fout, " (extern)");

					if (tp->i_scope & SCOPE_PUBLIC)
						fprintf(fout, " (public)");

					if (tp->i_scope & SCOPE_CMD_P)
						fprintf(fout, " (command line -P)");

					if (tp->i_scope & SCOPE_CMD_D)
						fprintf(fout, " (command line -D)");
				}
			}
		}
		lineout();
		putc('\n', fout);
	}
}




/*
 *  put out error report
 */
void erreport()
{
	int i, numerr, numwarn;

	if (!fout)
		return;

	if (line > 49) eject();
	lineout();
	numerr = 0;
	for (i=0; i<FIRSTWARN; i++) numerr += keeperr[i];
	numwarn = 0;
	for (i = FIRSTWARN; i < FLAGS; i++) numwarn += keeperr[i];
	if (numerr || numwarn) {
		fputs("\n\n\nError + Warning report:\n\n", fout);
		fprintf(fout, "%6d errors\n", numerr);
		fprintf(fout, "%6d warnings\n", numwarn);
		line += 6;
	} else {
		fputs("\n\n\nStatistics:\n", fout);
		line += 3;
	}

	for (i=0; i<FLAGS; i++)
		if (keeperr[i]) {
			lineout();
			fprintf(fout, "%6d %c -- %s %s\n",
				keeperr[i], errlet[i], errname[i],
				i < FIRSTWARN ? "error" : "warnings");
		}

	if (line > 52) eject();
	lineout();
	fprintf(fout, "\n%6d\tpasses\n", npass);
	fprintf(fout, "%6d\tjr promotions\n", njrpromo);
	fprintf(fout, "%6d\tsymbols\n", nitems);
	fprintf(fout, "%6d\tbytes\n", nbytes);
	line += 4;
	if (mfptr) {
		if (line > 53) eject();
		lineout();
		fprintf(fout, "\n%6d\tmacro calls\n", exp_number);
		fprintf(fout, "%6d\tmacro bytes\n", mfptr);
		fprintf(fout, "%6d\tinvented symbols\n", invented/2);
		line += 3;
	}
}

/*
 * count errors (GWP - added to set exit code)
 */
int counterr()
{
	int i, numerr = 0;
	for (i=0; i<FIRSTWARN; i++) numerr += keeperr[i];
	return numerr;
}

// Count warnings
int countwarn()
{
	int i, numwarn = 0;
	for (i = FIRSTWARN; i < FLAGS; i++)
		numwarn += keeperr[i];
	return numwarn;
}

char *mlook;

int nextmac()
{
	int ch;

	if (mlook) {
		if (*mlook) {
			ch = *mlook++;
			addtoline(ch);
		}
		else
			mlook = 0;
	}

	if (!mlook)
		ch = nextchar();

	return ch;
}

void putm_param_ref(struct item *param);
void putm_str(char *str, int look_for_param);

/*
 *  lexical analyser for macro definition
 */
void mlex(char *look)
{
	char  *p;
	int  c;
	int  t;
	int quote = 0, ampdrop = 0;
	struct item *param, *key;
	char symbuf[TEMPBUFSIZE];
	char *symbufmax = symbuf+TEMPBUFSIZE-1;

	/*
	 *  move text onto macro file, changing formal parameters
	 */
#ifdef	M_DEBUG
	fprintf(stderr,"enter 'mlex' at %d\n", mfptr) ;
#endif
	inmlex++;

	mlook = look;

	c = nextmac();
	for (;;) {
		int octo = 0, amp = 0, caret = 0;

		if (c == '#' || c == '&' || c == '^') {
			int esc = c;
			c = nextmac();
			if (charclass[c] != STARTER && charclass[c] != LETTER) {
				if (esc != '&' || !ampdrop)
					putm(esc);
				ampdrop = 0;
				continue;
			}
			if (esc == '#')
				octo = 1;
			else if (esc == '&')
				amp = 1;
			else
				caret = 1;
		}

		if (c == '%') {
			int next = nextmac();
			if (next == '%') {
				putm('\3'); // number of arguments.
				c = nextmac();
			}
			else {
				putm('%');
				c = next;
			}

			continue;
		}

		switch(charclass[c]) {

		case DIGIT:
			while (numpart[c]) {
				putm(c);
				c = nextmac();
			}
			continue;

		case STARTER:
		case LETTER:
			t = 0;
			p = symbuf;
			do {
				if (p >= symbufmax) {
					*symbufmax = '\0';
					printf("was parsing '%s' in macro definition\n", tempbuf);
					error(symlong);
				}
				*p++ = c;
				if (t < MAXSYMBOLSIZE)
					tempbuf[t++] = (c >= 'A' && c <= 'Z')  ?
						c+'a'-'A' : c;
				c = nextmac();
			} while	(charclass[c]==LETTER || charclass[c]==DIGIT || charclass[c]==STARTER);

			tempbuf[t] = 0;
			*p++ = '\0';
			p = symbuf;

			key = keyword(tempbuf);
			t = key ? key->i_token : 0;

			// Hmmm, that "item_lookup" is putting crap in the table, yes?
			if (mras)
				param = item_substr_lookup(tempbuf, MPARM, paramtab, PARAMTABSIZE);
			else
				param = item_lookup(tempbuf, paramtab, PARAMTABSIZE);

			// Accept almost anything as a parameter.  But a few
			// keywords will just screw things up royally.
			if (param && t != ENDM && t != REPT && t != IRPC && t != IRP && t != MACRO)
				t = param->i_token;

			// Caret escaping kills all expansion
			// And interpretation of ENDM, etc.  For better or worse.
			if (caret)
				t = 0;

			if (t == MPARM) {
				int pfx = octo || amp || c == '&';
				// # prefix only allowed if declared that way
				if (octo != param->i_scope)
					t = 0;
				else
					octo = 0;

				// Expansion in quoted strings only with prefix character.
				if (quote && !pfx && !zcompat)
					t = 0;

				amp = 0; // parameter substitution, eat '&'
			}
			else if (t && quote)
				t = 0;

			if (ampdrop)
				amp = 0;

			ampdrop = c == '&' && t == MPARM;

			if (octo) putm('#');
			if (amp) putm('&');

			if (t != MPARM) {
				putm(symbuf[0]);
				putm_str(symbuf + 1, mras && !quote);
			}
			else {
				putm_param_ref(param);
				// Only in MRAS will we have a remainder string
				putm_str(symbuf + strlen(param->i_string), mras && !quote);
			}

			if (t == ENDM) {
				if (--inmlex == 0)
					goto done;
			}
			else if (t == REPT || t == IRPC || t == IRP || t == MACRO) {
				inmlex++;
			}

			continue;

		case F_END:
			errwarn(warn_general, "macro definition went until end of file");
			if (expptr) {
				popsi();
				c = nextmac();
				continue;
			}

			goto done;

		default:
			switch (c) {
			case '\n':
				quote = 0;
				list1();
				break;
			case ';':
				if (!quote) {
					while (c != '\n' && c != 0) {
						putm(c);
						c = nextmac();
					}
					continue;
				}
				break;
			case '\'':
			case '"':
				if (c == quote)
					quote = 0;
				else
					quote = c;
				break;
			default:
				break;
			}
			if (c != '\1' && c != '`') putm(c);
			c = nextmac();
		}
	}

	/*
	 *  finish off the file entry
	 */
done:
	while(c != EOF && c != '\n' && c != '\0') c = nextmac();
	inmlex++;
	list1();
	inmlex--;
	// WHY two newlines??
//	putm('\n');
	putm('\n');
	putm(0);

	// TODO - here's where we could save parameter names for MRAS
	for (c = 0; c < PARAMTABSIZE; c++) {
		if (paramtab[c].i_token == MPARM) {
			free(paramtab[c].i_string);
			paramtab[c].i_string = NULL;
			paramtab[c].i_token = 0;
		}
	}
	inmlex = 0;
#ifdef	M_DEBUG
	fprintf(stderr,"exit 'mlex' at %d\n", mfptr) ;
#endif
}

void putm_param_ref(struct item *param)
{
	if (*(param->i_string) == '?' || param->i_chain)
		putm('\2');
	else
		putm('\1');

	putm(param->i_value + 'A');
}

void putm_str(char *str, int look_for_param)
{
	for (; *str; str++) {
		if (look_for_param) {
			struct item *param = item_substr_lookup(str, MPARM, paramtab, PARAMTABSIZE);
			if (param) {
				putm_param_ref(param);
				str += strlen(param->i_string) - 1;
				continue;
			}
		}
		putm(*str);
	}
}

int str_getch(struct argparse *ap)
{
	int ch = ap->user_peek;
	if (ch >= 0) {
		ap->user_peek = -1;
		return ch;
	}
	if (!ap->user_ptr || ap->user_ptr[ap->user_int] == '\0')
		return '\0';

	return ap->user_ptr[ap->user_int++];
}

int arg_getch(struct argparse *ap)
{
	(void)ap; // suppress warning
	return nextchar();
}

void arg_start()
{
	arg_reset();
	arg_flag = 1;
}

void arg_reset()
{
	arg_flag = 0;

	arg_state.arg = tempbuf;
	arg_state.argsize = sizeof tempbuf;
	arg_state.peek = &peekc;
	arg_state.getch = arg_getch;
	arg_state.macarg = 0;
	arg_state.user_ptr = 0;
	arg_state.user_int = 0;
	arg_state.didarg = 0;
	arg_state.numarg = 0;
}

/*
 *  lexical analyser for the arguments of a macro call
 */
int getarg(struct argparse *ap)
{
	int c;
	char *p;
	int quote;
	int depth;

	*ap->arg = 0;
	while (charclass[c = ap->getch(ap)] == SPACE);

	switch(c) {

	case '\0':
		if (!ap->user_ptr)
			popsi(); // a seemingly unlikely case?
	case '\n':
	case ';':
		if (!ap->didarg && ap->numarg) {
			*ap->peek = c;
			ap->didarg = 1;
			ap->numarg++;
			return ARG;
		}
		ap->didarg = 0;
		ap->numarg = 0;
		return c;

	case ',':
		if (!ap->didarg) {
			ap->didarg = 1;
			*ap->peek = c;
			ap->numarg++;
			return ARG;
		}
		ap->didarg = 0;
		return c;

	case '\'':
	case '\"':
		quote = c;
		p = ap->arg;
		if (!zcompat)
			*p++ = c;

		do {
			c = ap->getch(ap);
			if (c == '\0' || c == '\n') {
				*ap->peek = c;
				*p = 0;
				err[bflag]++;
				ap->didarg = 1;
				ap->numarg++;
				return ARG;
			}
			else if (c == quote) {
				if ((c = ap->getch(ap)) != quote) {
					if (!zcompat)
						*p++ = quote;
					*ap->peek = c;
					*p = '\0';
					ap->didarg = 1;
					ap->numarg++;
					return ARG;
				}
			}
			else
				*p++ = c;
		} while (p < ap->arg + ap->argsize - 1);
		ap->arg[ap->argsize - 1] = '\0';
		printf("was parsing macro argument '%s'\n", ap->arg);
		error(symlong);
		return 0; // not reached

	case '<':
		depth = 1;
		p = ap->arg;
		do {
			c = ap->getch(ap);
			if (c == '\0' || c == '\n') {
				*ap->peek = c;
				*p = 0;
				err[bflag]++;
				ap->didarg = 1;
				ap->numarg++;
				return ARG;
			}
			if (c == '>') {
				depth--;
				if (depth == 0) {
					*p = '\0';
					ap->didarg = 1;
					ap->numarg++;
					return ARG;
				}
			}
			else if (c == '<')
				depth++;

			*p++ = c;
		} while (p < ap->arg + ap->argsize - 1);
		ap->arg[ap->argsize - 1] = '\0';
		printf("was parsing macro argument '%s'\n", ap->arg);
		error(symlong);
		return 0; // not reached

	default:  /* unquoted string */
		if (c == '%' && ap->macarg) {
			ap->didarg = 1;
			ap->numarg++;
			return c;
		}

		p = ap->arg;
		*ap->peek = c;

		do {
			c = ap->getch(ap);
			switch(c) {
			case '\0':
			case '\n':
			case '\t':
			case ' ':
			case ',':
				*ap->peek = c;
				*p = '\0';
				ap->didarg = 1;
				ap->numarg++;
				return ARG;
			case '^':
				c = ap->getch(ap);
				switch (c) {
				case ',':
				case '^':
				case ' ':
				case '\t':
				case '%':
					*p++ = c;
					break;
				default:
					*p++ = '^';
					*ap->peek = c;
					break;
				}
				break;
			default:
				*p++ = c;
			}
		} while (p < ap->arg + ap->argsize - 1);
		ap->arg[ap->argsize - 1] = '\0';
		printf("was parsing macro argument '%s'\n", ap->arg);
		error("macro argument too long");
		return 0; // not reached
	}
}


/*
 *  add a suffix to a string
 */
void suffix(char *str, char *suff)
{
	strcpy(getsuffix(str), suff);
}

char *basename(char *filename)
{
	char *base, *p;

	base = filename;
	for (p = filename; *p; p++) {
		if (*p == '/' || *p == '\\') {
			base = p + 1;
		}
	}

	return base;
}

char *getsuffix(char *str)
{
	char *suffix = 0;
	str = basename(str);
	for (; *str; str++) {
		if (*str == '.')
			suffix = str;
	}
	return suffix ? suffix : str;
}

// Construct output file given input path.
// Essentially files for "file.z" are sent to "zout/file.suffix".
// And for "dir/file.z" they are "zout/file.suffix"
// Creates output directory as a side effect.

void outpath(char *out, char *src, char *suff)
{
	static int did_mkdir = 0;

	strcpy(out, output_dir);

	if (!did_mkdir) {
		char *dir = out;
		while (*dir) {
			char *p;
			int ch;
			for (p = dir; *p && *p != '/'
#ifdef WIN32
				 && *p != '\\'
#endif
				 ; p++) { };
			ch = *p;
			*p = '\0';
#ifdef WIN32
			_mkdir(out);
#else
			mkdir(out, 0777);
#endif
			*p = ch;
			dir = p;
			if (ch)
				dir++;
		}
		did_mkdir = 1;
	}

	if (!suff)
		return;

	if (*out)
		strcat(out, "/");
	strcat(out, basename(src));
	suffix(out, suff);
}


/*
 *  put out a byte to the macro file, keeping the offset
 */
void putm(int c)
{
	mfseek(mfile, mfptr, 0);
	mfptr++;
	mfputc(c, mfile);
}



/*
 *  get a byte from the macro file
 */
int getm()
{
	int ch;

	mfseek(mfile, floc, 0);
	floc++;
	ch = mfgetc(mfile);
	if (ch == EOF) {
		ch = 0;
		fprintf(stderr, "bad macro read\n");
	}
	return ch;
}



/*
 *  pop standard input
 */
void popsi()
{
	int  i;

	for (i=0; i<PARMMAX; i++) {
		if (est[i].param) free(est[i].param);
	}
	floc = est[FLOC].value;
	ifptr = est[MIF].param;
	free(est);
	expptr--;
	est = expptr ? expstack[expptr-1] : 0;
	mfseek(mfile, (long)floc, 0);
	if (lineptr > linebuf) lineptr--;

	listfrombookmark();
}



/*
 *  return a unique name for a local symbol
 *  c is the parameter number, n is the macro number.
 */

char *getlocal(int c, int n)
{
	static char local_label[10];

	invented++;
	if (c >= 26)
		c += 'a' - '0';
	sprintf(local_label, "?%c%04d", c+'a', n) ;
	return(local_label);
}

char *getmraslocal()
{
	static char mras_local[32];
	char *p = mras_local + sizeof mras_local - 1;
	int n = est[TEMPNUM].value;

	*p = '\0';
	for (; n > 0; n /= 26)
		*--p = 'A' + n % 26;


	return p;
}


/*
 *  read in a symbol table
 */
void insymtab(char *name)
{
	struct stab *t;
	int  s, i;
	FILE *sfile;

	t = (struct stab *) tempbuf;
	if (!(sfile = fopen(name, "rb")))
		return;
	fread((char *)t, 1, sizeof *t, sfile);
	if (t->t_value != SYMMAJIC)
		return;

	
	s = t->t_token;
	for (i=0; i<s; i++) {
		fread((char *)t, 1, sizeof *t, sfile);
		if (tokenofitem(UNDECLARED, 0, 0) != UNDECLARED)
			continue;
		yylval.itemptr->i_token = t->t_token;
		yylval.itemptr->i_value = t->t_value;
		if (t->t_token == MACRO)
			yylval.itemptr->i_value += mfptr;
	}

	while ((s = fread(tempbuf, 1, TEMPBUFSIZE, sfile)) > 0) {
		mfptr += s;
		mfwrite(tempbuf, 1, s, mfile) ;
	}
	fclose(sfile);
}



/*
 *  write out symbol table
 */
void outsymtab(char *name)
{
	struct stab *t;
	struct item *ip;
	int  i;
	FILE *sfile;

	t = (struct stab *) tempbuf;
	if (!(sfile = fopen(name, "wb")))
		return;
	for (ip=itemtab; ip<itemmax; ip++) {
		if (ip->i_token == UNDECLARED) {
			ip->i_token = 0;
			nitems--;
		}
	}

	copyname(title, (char *)t);
	t->t_value = SYMMAJIC;
	t->t_token = nitems;
	fwrite((char *)t, 1, sizeof *t, sfile);

	for (ip=itemtab; ip<itemmax; ip++) {
		if (ip->i_token != 0) {
			t->t_token = ip->i_token;
			t->t_value = ip->i_value;
			copyname(ip->i_string, (char *)t);
			fwrite((char *)t, 1, sizeof *t, sfile);
		}
	}

	mfseek(mfile, (long)0, 0);
	while((i = mfread(tempbuf, 1, TEMPBUFSIZE, mfile) ) > 0)
		fwrite(tempbuf, 1, i, sfile);

	fclose(sfile);
}



/*
 *  copy a name into the symbol file
 */
void copyname(char *st1, char *st2)
{
	char  *s1, *s2;
	int  i;

	i = (MAXSYMBOLSIZE+2) & ~01;
	s1 = st1;
	s2 = st2;

	while((*s2++ = *s1++)) i--;		/* -Wall-ishness :-) -RJM */
	while(--i > 0) *s2++ = '\0';
}

/* get the next source file */
void next_source(char *sp, int always)
{
	char *path;

	if (!always && imported(sp))
		return;

	if(now_in == NEST_IN -1)
		error("Too many nested includes") ;
	if ((now_file = open_incpath(sp, "r", &path)) == NULL) {
		char ebuf[1024] ;
		sprintf(ebuf,"Can't open include file: %s", sp) ;
		error(ebuf) ;
	}
	if (outpass && iflist()) {
		lineout() ;
		fprintf(fout, "**** %s ****\n", path) ;
	}

	if (outpass && fbds)
		fprintf(fbds, "%04x %04x f %s\n", dollarsign, emit_addr, sp);

	/* save the list control flag with the current line number */
	if (lstoff)
		linein[now_in] = - linein[now_in] ;

	/* no list if include files are turned off */
	lstoff |= iopt ;

	linepeek[now_in] = nextline_peek;
	nextline_peek = NOPEEK;
	/* save the new file descriptor. */
	fin[++now_in] = now_file ;
	/* start with line 0 */
	linein[now_in] = 0 ;
	/* save away the file name */
	src_name[now_in] = path;
}

int phaseaddr(int addr)
{
	if (!phaseflag)
		return addr;

	if (addr < phbegin || addr > dollarsign) {
		err[vflag]++;
		if (pass2)
			fprintf(stderr, "$%04x outside current phase area\n", addr);
		return 0;
	}

	return phdollar + (addr - phbegin);
}

// Include contents of named file as binary data.
void incbin(char *filename)
{
	FILE *fp = open_incpath(filename, "rb", NULL);
	int ch;
	int start = dollarsign;
	int last = start;
	int bds_count;
	int bds_dollar = dollarsign, bds_addr = emit_addr, bds_len;

	if (!fp) {
		char ebuf[1024];
		sprintf(ebuf, "Can't binary include file: %s", filename);
		error(ebuf);
		return;
	}

	addtoline('\0');
	if (outpass && fbds)
		fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, linebuf);

	// Avoid emit() because it has a small buffer and it'll spam the listing.
	bds_count = 0;
	bds_len = 0;
	while ((ch = fgetc(fp)) != EOF) {
		if (outpass && fbds) {
			if (bds_count == 0)
				fprintf(fbds, "%04x %04x d ", dollarsign, emit_addr);
			fprintf(fbds, "%02x", ch);
			bds_len++;
			bds_count++;
			if (bds_count == 16) {
				fprintf(fbds, "\n");
				bds_count = 0;
			}
		}

		if (segment == SEG_CODE)
			setmem(emit_addr, ch, MEM_DATA);
		emit_addr++;
		emit_addr &= 0xffff;
		last = dollarsign;
		dollarsign++;
		dollarsign &= 0xffff;

		putbin(ch);
		putrel(ch);
		putout(ch);
	}
	if (outpass && fbds) {
		if (bds_count)
			fprintf(fbds, "\n");

		bds_perm(bds_dollar, bds_addr, bds_len);
	}

	fclose(fp);

	// Do our own list() work as we emit bytes manually.

	if (outpass && iflist()) {
		lineout();

		if (nopt)
			fprintf(fout, "%4d:", linein[now_in]);

		if (copt)
		        fprintf(fout, nopt ? "%5s-" : "%4s-", "");

		if (nopt || copt)
			fprintf(fout, "\t");

		list_optarg(start, -1, 0);
		fprintf(fout, "..");
		list_optarg(last, -1, 0);

		putc('\t', fout);

		fputs(linebuf, fout);

	}
	lineptr = linebuf;
}

void dc(int count, int value)
{
	int start = dollarsign;
	int bds_count;
	int bds_addr = emit_addr, bds_len = count;

	addtoline('\0');
	if (outpass && fbds)
		fprintf(fbds, "%04x %04x s %s", dollarsign, emit_addr, linebuf);

	// Avoid emit() because it has a small buffer and it'll spam the listing.
	bds_count = 0;
	while (count-- > 0) {
		if (outpass && fbds) {
			if (bds_count == 0)
				fprintf(fbds, "%04x %04x d ", dollarsign, emit_addr);
			fprintf(fbds, "%02x", value);
			bds_count++;
			if (bds_count == 16) {
				fprintf(fbds, "\n");
				bds_count = 0;
			}
		}

		if (segment == SEG_CODE)
			setmem(emit_addr, value, MEM_DATA);

		emit_addr++;
		emit_addr &= 0xffff;
		dollarsign++;
		dollarsign &= 0xffff;

		putbin(value);
		putrel(value);
		putout(value);
	}

	if (outpass && fbds) {
		if (bds_count)
			fprintf(fbds, "\n");

		bds_perm(start, bds_addr, bds_len);
	}

	// Do our own list() work as we emit bytes manually.

	if (outpass && iflist()) {
		lineout();

		if (nopt)
			fprintf(fout, "%4d:", linein[now_in]);

		if (copt)
		        fprintf(fout, nopt ? "%5s-" : "%4s-", "");

		if (nopt || copt)
			fprintf(fout, "\t");

		list_optarg(start, -1, 0);
		fprintf(fout, "..");
		list_optarg(dollarsign - 1, -1, 0);
		puthex(value, fout);
		putc('\t', fout);
		fputs(linebuf, fout);
		lsterr2(1);

	}
	else
		lsterr1();

	lineptr = linebuf;
}

#define OUTREC_SEG(rec)		outbuf[rec]
#define OUTREC_ADDR(rec)	((outbuf[rec + 1] << 8) | outbuf[rec + 2])
#define OUTREC_LEN(rec)		outbuf[rec + 3]
#define OUTREC_DATA(rec, len)	outbuf[rec + 4 + len]
#define OUTREC_SIZEOF	5

void new_outrec(void)
{
	OUTREC_LEN(outrec) = outlen;
	outrec += OUTREC_SIZEOF + outlen;

	outlen = 0;
	OUTREC_SEG(outrec) = segment;
	outbuf[outrec + 1] = seg_pos[segment] >> 8;
	outbuf[outrec + 2] = seg_pos[segment];
}

void putout(int value)
{
	int addr = (OUTREC_ADDR(outrec) + outlen) & 0xffff;
	if (OUTREC_SEG(outrec) != segment || addr != seg_pos[segment])
		new_outrec();

	if (pass2 && OUTREC_DATA(outrec, outlen) != value && !passfail) {
		char segname[2];
		if (relopt)
			sprintf(segname, "%c", SEGCHAR(segment));
		else
			segname[0] = '\0';

		sprintf(detail, "%s error - $%04x%s changed from $%02x to $%02x",
			errname[pflag], addr, segname, OUTREC_DATA(outrec, outlen), value);
		errwarn(pflag, detail);

		if (!outpass)
			passretry = 1;
	}
	OUTREC_DATA(outrec, outlen) = value;
	outlen++;

	if (outlen >= 255)
		new_outrec();

	advance_segment(1);
}

struct bookmark {
	int len, rec, tstates, linenum, listed;
	char *line;
}
bookstack[MAXEXP];

int mark;

void bookmark(int delay)
{
	struct bookmark *book;

	if (!outpass)
		return;

	if (mark >= MAXEXP) {
		error("Macro expansion level too deep");
		return;
	}

	book = bookstack + mark++;

	book->len = outlen;
	book->rec = outrec;
	book->tstates = tstates;
	book->linenum = linein[now_in];
	book->line = strdup(linebuf);
	book->listed = !delay;
}

int book_row, book_col, book_addr, book_seg;

void booklist(int seg, int addr, int data, struct bookmark *book)
{
	// Don't list beyond the first 4 bytes if told not to.
	if (!gopt && book_row > 0)
		return;

	if (book_addr == -1) {
		list_optarg(addr, seg, ' ');
		book_seg = seg;
		book_addr = addr;
		book_col = 0;
	}

	if (seg != book_seg || addr != book_addr || book_col < 0 || book_col == 4) {
		if (book_row == 0 && book->line) {
			fprintf(fout, "\t%s", book->line);
			free(book->line);
			book->line = 0;
		}
		else
			fputs("\n", fout);

		lineout();

		book_row++;
		book_col = 0;

		if (!gopt && !book->line)
			return;

		if (nopt) putc('\t', fout);
		if (copt) fputs("        ", fout);

		if (seg != book_seg || addr != book_addr)
			list_optarg(addr, seg, ' ');
		else
			fputs("      ", fout);

		book_seg = seg;
		book_addr = addr;
	}

	if (!gopt && book_row > 0)
		return;

	puthex(data, fout);
	book_addr++;
	book_col++;
}

void listfrombookmark()
{
	int t, n;
	struct bookmark *book;

	if (!outpass)
		return;

	if (mark < 1) {
		//error("Internal delayed listing underflow.");
		fprintf(stderr, "Internal delayed listing underflow at %d.", mark);
		return;
	}

	book = bookstack + --mark;

	// No delayed listing required?  bookstack clean is all we need.
	if (book->listed) {
		if (book->line) {
			free(book->line);
			book->line = 0;
		}
		return;
	}

	book->listed = 1;

	t = tstates - book->tstates;
	lineout(); // call before every output line

	if (nopt)
		fprintf(fout, "%4d:", book->linenum);

	if (copt) {
		if (t) {
			fprintf(fout, nopt ? "%5d+%d" : "%4d+%d", book->tstates, t);
		}
		else {
			fprintf(fout, nopt ? "%5s-" : "%4s-", "");
		}
	}

	if (nopt || copt)
		fprintf(fout, "\t");

	book_row = 0;
	book_col = -1;
	book_addr = -1;
	n = 0;
	while (book->rec <= outrec) {
		int len = book->rec == outrec ? outlen : OUTREC_LEN(book->rec);
		int addr = OUTREC_ADDR(book->rec) + book->len;
		int seg = OUTREC_SEG(book->rec);

		for (; book->len < len; book->len++) {
			booklist(seg, addr++, OUTREC_DATA(book->rec, book->len), book);
			n++;
		}

		book->len = 0;
		book->rec += OUTREC_SIZEOF + len;
	}

	if (book->line) {
		// pad with spaces up to 4 total hex bytes
		for (; n < 4; n++)
			fprintf(fout, "  ");

		fprintf(fout, "\t%s", book->line);
		free(book->line);
		book->line = 0;
	}
	else if (gopt)
		fputs("\n", fout);
}

void advance_segment(int step)
{
	int top = seg_pos[segment] += step;
	seg_pos[segment] &= 0xffff;
	if (top >= 0x10000)
		top = 0xffff;

	if (top > seg_size[segment]) {
		seg_size[segment] = top;
		if (segment == SEG_COMMON && cur_common)
			cur_common->i_value = top;
	}
}

void expr_reloc_check(struct expr *ex)
{
	if (!relopt) return;
	if (ex->e_scope & (SCOPE_EXTERNAL | SCOPE_NORELOC))
		err[rflag]++;
}

void expr_number_check(struct expr *ex)
{
	if (!relopt) return;
	expr_reloc_check(ex);
	if (ex->e_scope & SCOPE_SEGMASK)
		err[rflag]++;
}

void expr_scope_same(struct expr *ex1, struct expr *ex2)
{
	if (!relopt) return;
	if ((ex1->e_scope & SCOPE_SEGMASK) != (ex2->e_scope & SCOPE_SEGMASK))
		err[rflag]++;
}

void expr_word_check(struct expr *ex)
{
	if (ex->e_value < -32768 || ex->e_value > 65535) {
		err[vflag]++;
	}
}

int is_number(struct expr *ex)
{
	return ex && (ex->e_scope & ~(SCOPE_PUBLIC | SCOPE_TWOCHAR)) == 0;
}

int is_external(struct expr *ex)
{
	return ex && (ex->e_scope & SCOPE_EXTERNAL) && !ex->e_left && !ex->e_right &&
		ex->e_item;
}

struct expr *expr_alloc(void)
{
	struct expr *ex = malloc(sizeof *ex);

	ex->e_value = 0;
	ex->e_scope = 0;
	ex->e_token = 0;
	ex->e_item = 0;
	ex->e_left = 0;
	ex->e_right = 0;
	ex->e_parenthesized = 0;

	return ex;
}

struct expr *expr_var(struct item *it)
{
	struct expr *ex = expr_alloc();

	ex->e_token = 'v';
	ex->e_item = it;
	ex->e_scope = it->i_scope;
	ex->e_value = it->i_value;

	return ex;
}

struct expr *expr_num(int value)
{
	struct expr *ex = expr_alloc();
	ex->e_value = value;
	ex->e_token = '0';

	return ex;
}

// Build expression and update value based on the operator.
// Could be done inline in the grammar but there is a fair bit of
// repetition and MRAS operators have only made that worse.

struct expr *expr_mk(struct expr *left, int op, struct expr *right)
{
	struct expr *ex;
	int val = 0;
	int sc = 0;

	switch (op) {
	case '+':
		ex = expr_op(left, '+', right, left->e_value + right->e_value);

		// Can't operate on external labels.
		// But we can add constants to any scope.
		if (!((left->e_scope | right->e_scope) & SCOPE_EXTERNAL) &&
			((left->e_scope & SCOPE_SEGMASK) == 0 ||
			(right->e_scope & SCOPE_SEGMASK) == 0))
		{
			ex->e_scope &= ~(SCOPE_NORELOC | SCOPE_SEGMASK);
			ex->e_scope |= (left->e_scope | right->e_scope) & SCOPE_SEGMASK;
		}
		return ex;
	case '-':
		ex = expr_op_sc(left, '-', right, left->e_value - right->e_value);

		// But we can subtract a constant.
		if (!((left->e_scope | right->e_scope) & SCOPE_EXTERNAL) &&
			((right->e_scope & SCOPE_SEGMASK) == 0))
		{
			ex->e_scope &= ~(SCOPE_NORELOC | SCOPE_SEGMASK);
			ex->e_scope |= (left->e_scope & SCOPE_SEGMASK);
		}
		return ex;
	case '/':
		if (!(right->e_scope & SCOPE_EXTERNAL)) {
			if (right->e_value == 0)
				err[eflag]++;
			else
				val = left->e_value / right->e_value;
		}
		break;
	case '*':
		val = left->e_value * right->e_value;
		break;
	case '%':
		if (!(right->e_scope & SCOPE_EXTERNAL)) {
			if (right->e_value == 0)
				err[eflag]++;
			else
				val = left->e_value % right->e_value;
		}
		break;
	case '&':
		val = left->e_value & right->e_value;
		break;
	case '|':
		val = left->e_value | right->e_value;
		break;
	case '^':
		val = left->e_value ^ right->e_value;
		break;
	case SHL:
		val = left->e_value << right->e_value;
		break;
	case SHR:
		val = right->e_value == 0 ? left->e_value : ((left->e_value >> 1) & ((0x7fff << 16) | 0xffff)) >> (right->e_value - 1);
		break;
	case '<':
		val = (left->e_value < right->e_value) * trueval;
		sc = 1;
		break;
	case '=':
		val = (left->e_value == right->e_value) * trueval;
		sc = 1;
		break;
	case '>':
		val = (left->e_value > right->e_value) * trueval;
		sc = 1;
		break;
	case LE:
		val = (left->e_value <= right->e_value) * trueval;
		sc = 1;
		break;
	case NE:
		val = (left->e_value != right->e_value) * trueval;
		sc = 1;
		break;
	case GE:
		val = (left->e_value >= right->e_value) * trueval;
		sc = 1;
		break;
	case ANDAND:
		val = (left->e_value && right->e_value) * trueval;
		break;
	case OROR:
		val = (left->e_value || right->e_value) * trueval;
		break;
	default:
		fprintf(stderr, "internal expression evaluation error!\n");
		clean_outf();
		exit(-1);
		break;
	}

	if (sc)
		return expr_op_sc(left, op, right, val);

	return expr_op(left, op, right, val);
}


// Expression consruction for operators that subtract/compare.
// They produce a valid result if operating on numbers in the same segment.
struct expr *expr_op_sc(struct expr *left, int token, struct expr *right, int value)
{
	struct expr *ex = expr_op(left, token, right, value);

	if (!(ex->e_scope & SCOPE_EXTERNAL) &&
		((left->e_scope ^ right->e_scope) & SCOPE_SEGMASK) == 0)
	{
		// Result relocatable and a simple number
		ex->e_scope &= ~(SCOPE_NORELOC | SCOPE_SEGMASK);
	}

	return ex;
}

struct expr *expr_op(struct expr *left, int token, struct expr *right, int value)
{
	struct expr *ex = expr_alloc();

	ex->e_value = value;
	ex->e_token = token;
	ex->e_left = left;
	ex->e_right = right;

	// Combining two numbers will be fine as long as they're not
	// flagged as external or already not relocatable.  In which case
	// it is up to the particular operator to allow the value
	// to become valid.

	ex->e_scope = left->e_scope;
	if (left->e_scope & SCOPE_SEGMASK)
		ex->e_scope |= SCOPE_NORELOC;
	if (right) {
		ex->e_scope |= right->e_scope;
		if (right->e_scope & SCOPE_SEGMASK)
			ex->e_scope |= SCOPE_NORELOC;
	}

	return ex;
}

void expr_free(struct expr *ex)
{
	if (!ex)
		return;

	expr_free(ex->e_left);
	expr_free(ex->e_right);
	free(ex);
}

int synth_op(struct expr *ex, int gen)
{
	if (!is_number(ex->e_right))
		return 0;

	switch (ex->e_token) {
	case '&':
		if (ex->e_right->e_value == 255) {
			if (gen) {
				extend_link(ex->e_left);
				putrelop(RELOP_LOW);
				return 1;
			}
			return can_extend_link(ex->e_left);
		}
		break;
	case SHR:
		if (ex->e_right->e_value <= 15) {
			if (gen) {
				extend_link(ex->e_left);
				extend_link(expr_num(1 << ex->e_right->e_value));
				putrelop(RELOP_DIV);
			}
			return can_extend_link(ex->e_left);
		}
		break;
	case SHL:
		if (ex->e_right->e_value <= 15) {
			if (gen) {
				extend_link(ex->e_left);
				extend_link(expr_num(1 << ex->e_right->e_value));
				putrelop(RELOP_MUL);
			}
			return can_extend_link(ex->e_left);
		}
		break;
	default:
		break;
	}

	return 0;
}

int link_op(struct expr *ex)
{
	if (!ex)
		return 0;

	switch (ex->e_token) {
	case HIGH: return RELOP_HIGH;
	case LOW: return RELOP_LOW;
	case '~': return RELOP_NOT;
	case '-': return !ex->e_right ? RELOP_NEG : RELOP_SUB;
	case '+': return RELOP_ADD;
	case '*': return RELOP_MUL;
	case '/': return RELOP_DIV;
	case '%': return RELOP_MOD;
	default: return 0;
	}
}

int can_extend_link(struct expr *ex)
{
	if (!ex)
		return 1;

	// If we have a value available then we're good.
	if (!(ex->e_scope & SCOPE_NORELOC)) {
		//printf("HEY!\n");
		//if (ex->e_item && ex->e_item->i_string)
		//	printf("ext link says OK for '%s'\n", ex->e_item->i_string);
		return 1;
	}

	// Might be able to synthesize the operation.
	if (synth_op(ex, 0))
		return 1;

	// Otherwise, the operator must be supported and the children
	// must be linkable.

	return link_op(ex) && can_extend_link(ex->e_left) && can_extend_link(ex->e_right);
}

void extend_link(struct expr *ex)
{
	int op;

	if (!ex)
		return;

	if (synth_op(ex, 1))
		return;

	extend_link(ex->e_left);
	extend_link(ex->e_right);

	op = link_op(ex);
	if (op) {
		putrelop(op);
		return;
	}

	putrelcmd(RELCMD_EXTLINK);

	if (is_external(ex)) {
		char *str = ex->e_item->i_string;
		int len = strlen(str);

		if (len > 6)
			len = 6;

		putrelbits(3, 1 + len);
		putrelbits(8, 'B');
		while (len-- > 0) {
			int ch = *str++;
			if (ch >= 'a' && ch <= 'z')
				ch -= 'a' - 'A';
			putrelbits(8, ch);
		}
	}
	else {
		putrelbits(3, 4);
		putrelbits(8, 'C');
		putrelbits(8, ex->e_scope & SCOPE_SEGMASK);
		putrelbits(8, ex->e_value);
		putrelbits(8, ex->e_value >> 8);
	}
}

void putrelop(int op)
{
	putrelcmd(RELCMD_EXTLINK);

	putrelbits(3, 2);
	putrelbits(8, 'A');
	putrelbits(8, op);
}

void write_tap_block(int type, int len, unsigned char *data)
{
	int i, parity;

	fputc((len + 2) & 0xff, ftap);
	fputc((len + 2) >> 8, ftap);

	fputc(type, ftap);
	parity = type;
	for (i = 0; i < len; i++) {
		fputc(data[i], ftap);
		parity ^= data[i];
	}
	fputc(parity, ftap);
}

// One supposes .tap files could load multiple blocks into memory.
// However, doesn't seem to be a lot of point and we'd have to write
// extra loader code to make it happen.  For now we just load the
// assembled data as one contiguous block with the holes getting
// filled with zeros.

void write_tap(int len, int org, unsigned char *data)
{
	unsigned char block[32], *p, orglo, orghi;
	unsigned char basic_loader[] = {
		239, 34, 34, 175, 58, 249, 192, 176, // LOAD ""CODE:RANDOMIZE USR VAL
		'"', '2', '3', '2', '9', '6', '"', 13 // aka 0x5b00 - start of RAM
	};
	int entry = org;

	if (xeq_flag)
		entry = xeq;

	// .tap file output borrowed heavily from skoolkit's bin2tap.py
	// It loads a short basic program which auto-executes and loads
	// a short machine-language loader that reads the block of code
	// and jumps to it.
	// Constrast this with pasmo which doesn't have the short machine
	// code loader but uses a native code block.  I think that means
	// it can only execute at the beginning of the loaded data.

	p = block;

	*p++ = 0; // Program block
	casname((char *)p, sourcef, 10);
	p += 10;
	*p++ = 4 + sizeof basic_loader; *p++ = 0; // length of BASIC program
	*p++ = 10; *p++ = 0; // run line 10 after loading
	*p++ = 4 + sizeof basic_loader; *p++ = 0; // length of BASIC program

	write_tap_block(0, p - block, block);

	p = block;
	*p++ = 0; *p++ = 10; // line 10
	*p++ = sizeof(basic_loader); *p++ = 0;
	memcpy(p, basic_loader, sizeof basic_loader);
	p += sizeof basic_loader;
	write_tap_block(0xff, p - block, block);

	p = block;

	*p++ = 3; // Code block
	casname((char *)p, sourcef, 10);
	p += 10;
	*p++ = 19; *p++ = 0; // length of loader program
	*p++ = 0; *p++ = 0x5b; // 0x5b00 == 23296 - start of RAM
	*p++ = 0; *p++ = 0; // ?

	write_tap_block(0, p - block, block);

	p = block;

	orglo = org & 0xff;
	orghi = org >> 8;
	/* LD IX,org   */ *p++ = 0xdd; *p++ = 0x21; *p++ = orglo; *p++ = orghi;
	/* LD DE,len   */ *p++ = 0x11; *p++ = len & 0xff; *p++ = len >> 8;
	/* SCF         */ *p++ = 0x37;
	/* SBC A,A     */ *p++ = 0x9f;
	/* LD SP,org   */ *p++ = 0x31; *p++ = orglo; *p++ = orghi;
	/* LD BC,entry */ *p++ = 0x01; *p++ = entry & 0xff; *p++ = entry >> 8;
	/* PUSH BC     */ *p++ = 0xc5;
	/* JP $556     */ *p++ = 0xc3; *p++ = 0x56; *p++ = 0x05;

	write_tap_block(0xff, p - block, block);

	write_tap_block(0xff, len, data);
}

#define WORD(w) (w) & 255, (w) >> 8

void write_250(int low, int high)
{
	int load = low;
	int len = high - low + 1;
	int last;
	int chk;

	if (len <= 0) {
		// Nothing to output.  So we'll just delete the output file.
		int i;
		for (i = 0; i < CNT_OUTF; i++) {
			if (*outf[i].fpp && (*outf[i].fpp == ftcas || *outf[i].fpp == f250wav)) {
				fclose(*outf[i].fpp);
				*outf[i].fpp = NULL;
				unlink(outf[i].filename);
				if (outf[i].wanted)
					fprintf(stderr, "Warning: %s not output -- no code or data\n", outf[i].filename);
			}
		}
		return;
	}

	if (xeq_flag) {
		// Only add relocation if they don't already put their
		// execution address in to $41FE.  This means programs will
		// be unchanged if they seem to be aware of the structure.

		if (low > 0x41FE || high < 0x41FF ||
			memory[0x41FE] != (xeq & 0xff) ||
			memory[0x41FF] != xeq >> 8)
		{
			if (low >= 0x4200 && low <= 0x4200 + 14) {
				// A little too high.  More efficient to
				// just load a bit extra.  Plus we can't
				// easily fit in the "copy up" code.
				low = 0x41FE;
				memory[0x41FE] = xeq;
				memory[0x41FF] = xeq >> 8;
				load = low;
			}
			else if (low < 0x4200) {
				// Moving down.
				int src = 0x4200;
				int dst = low;
				unsigned char relo[] = {
					0x21, WORD(src),	// LD HL,nn
					0x11, WORD(dst),	// LD DE,nn
					0x01, WORD(len),	// LD BC,len
					0xED, 0xB0,		// LDIR
					0xC3, WORD(xeq)		// JP nn
				};
				high++;
				low -= 2;
				memory[low] = src + len;
				memory[low + 1] = (src + len) >> 8;
				memcpy(memory + high, relo, sizeof relo);
				high += sizeof relo - 1;
				load = 0x41FE;
			}
			else {
				// Moving up
				int src = 0x41FE + 2 + 14 + len - 1;
				int dst = low + len - 1;
				unsigned char relo[] = {
					WORD(0x4200),
					0x21, WORD(src),	// LD HL,nn
					0x11, WORD(dst),	// LD DE,nn
					0x01, WORD(len),	// LD BC,len
					0xED, 0xB8,		// LDDR
					0xC3, WORD(xeq)		// JP nn
				};
				low -= sizeof relo;
				memcpy(memory + low, relo, sizeof relo);
				load = 0x41FE;
			}
		}
	}

	len = high + 1 - low;
	last = load + len;
	// Yeah, it is big endian.
	fprintf(ftcas, "%c%c%c%c", load >> 8, load, last >> 8, last);
	fwrite(memory + low, len, 1, ftcas);
	chk = 0;
	for (i = 0; i < len; i++)
		chk += memory[low + i];
	fprintf(ftcas, "%c", -chk);
}

int bitgetbuf;
int bitgetcnt;

void bitget_rewind(FILE *fp)
{
	bitgetcnt = 0;
	fseek(fp, 0, SEEK_SET);
}

int bitget(FILE *fp)
{
	int bit;

	if (bitgetcnt == 0) {
		bitgetbuf = fgetc(fp);
		bitgetcnt = 8;
	}

	bit = !!(bitgetbuf & 0x80);
	bitgetbuf <<= 1;
	bitgetcnt--;

	return bit;
}

void writewavs(int pad250, int pad500, int pad1500)
{
	FILE *cas[] = { ftcas, flcas, flnwcas, fcas };
	FILE *wav[] = { f250wav, f500wav, f1000wav, f1500wav };
	int padbits[] = { pad250, pad500, pad500, pad1500 };
#define	NFMT (sizeof padbits / sizeof padbits[0])
	int bits[NFMT];
	int i, j, k, m;
#define MAXA 0xfc
#define MIDA 0x80
#define MINA 4
	unsigned char intro[] = { MIDA, MIDA, MIDA, MINA };
	unsigned char pulse[][2][13] = {
		{ { 2, MAXA, 2, MINA, 42 - 4, MIDA, 0 },
		  { 2, MAXA, 2, MINA, 17, MIDA, 2, MAXA, 2, MINA, 17, MIDA, 0 } },

		{ { 3, MAXA, 3, MINA, 44 - 6, MIDA, 0 },
		  { 3, MAXA, 3, MINA, 16, MIDA, 3, MAXA, 3, MINA, 16, MIDA, 0 } },

		{ { 3, MAXA, 3, MINA, 44 - 6, MIDA, 0 },
		  { 3, MAXA, 3, MINA, 16, MIDA, 3, MAXA, 3, MINA, 16, MIDA, 0 } },

		{ { 8, MAXA, 8, MINA, 0 },
		  { 4, MAXA, 4, MINA, 0 } }
	};
	unsigned char outro[] = { MIDA, MIDA, MIDA, MAXA };
	int hz[] = { 11025, 22050, 44100, 22050 };
	int pulse_len[NFMT][2];

	for (i = 0; i < NFMT; i++) {
		for (j = 0; j < 2; j++) {
			pulse_len[i][j] = 0;
			for (k = 0; pulse[i][j][k]; k += 2)
				pulse_len[i][j] += pulse[i][j][k];
		}
	}

	for (i = 0; i < NFMT; i++) {
		if (!cas[i] || !wav[i])
			continue;

		bits[i] = ftell(cas[i]) * 8 - padbits[i];
	}

	for (i = 0; i < NFMT; i++) {
		int headPad = 10, tailPad = hz[i] / 2;
		int audio_bytes = headPad;
		unsigned char hzlo = hz[i] & 0xff;
		unsigned char hzhi = hz[i] >> 8;

		unsigned char waveHeader[] = {
			'R', 'I', 'F', 'F',
			0, 0, 0, 0,
			'W', 'A', 'V', 'E', 'f', 'm', 't', ' ',
			16, 0, 0, 0, // wav information length
			1, 0, // PCM
			1, 0, // Single channel
			hzlo, hzhi, 0, 0, // samples/second
			hzlo, hzhi, 0, 0, // average bytes/second
			1, 0, // block alignment
			8, 0, // bits/sample
			'd', 'a', 't', 'a',
			0, 0, 0, 0
		};
		int waveHeaderSize = sizeof waveHeader;

		if (!cas[i] || !wav[i])
			continue;

		bitget_rewind(cas[i]);
		for (j = 0; j < bits[i]; j++)
			audio_bytes += pulse_len[i][bitget(cas[i])];

		audio_bytes += tailPad;

		waveHeader[waveHeaderSize - 4] = audio_bytes;
		waveHeader[waveHeaderSize - 3] = audio_bytes >> 8;
		waveHeader[waveHeaderSize - 2] = audio_bytes >> 16;
		waveHeader[waveHeaderSize - 1] = audio_bytes >> 24;

		waveHeader[4] = (audio_bytes + 36);
		waveHeader[5] = (audio_bytes + 36) >> 8;
		waveHeader[6] = (audio_bytes + 36) >> 16;
		waveHeader[7] = (audio_bytes + 36) >> 24;

		bitget_rewind(cas[i]);

		fwrite(waveHeader, waveHeaderSize, 1, wav[i]);

		for (j = 0; j < headPad; j++)
			fputc(intro[i], wav[i]);

		bitget_rewind(cas[i]);
		for (j = 0; j < bits[i]; j++) {
			int bit = bitget(cas[i]);
			for (k = 0; pulse[i][bit][k]; k += 2)
				for (m = 0; m < pulse[i][bit][k]; m++)
					fputc(pulse[i][bit][k + 1], wav[i]);
		}

		for (j = 0; j < tailPad; j++)
			fputc(outro[i], wav[i]);
	}
#undef NFMT
#undef MAXA
#undef MIDA
#undef MINA
}

int sized_byteswap(int value)
{
	int swapped = 0;

	for (; value; value = (value >> 8) & 0xffffff) {
		swapped <<= 8;
		swapped |= value & 0xff;
	}

	return swapped;
}

// Tracking whether a file has been imported.

struct import_list {
	struct import_list *next;
	char *filename;
	int imported;
} *imports;

void reset_import()
{
	struct import_list *il;
	for (il = imports; il; il = il->next)
		il->imported = 0;
}

// Returns 1 if filename has been imported.  Marks it as imported.
// Only uses the base name.

int imported(char *filename)
{
	struct import_list *il;
	int ret;
	char *p;

	for (p = filename; *p; p++)
		if (*p == '/' || *p == '\\')
			filename = p + 1;

	for (il = imports; il; il = il->next) {
		if (strcmp(filename, il->filename) == 0)
			break;
	}

	if (!il) {
		il = malloc(sizeof *il);
		il->filename = strdup(filename);
		il->imported = 0;
		il->next = imports;
		imports = il;
	}

	ret = il->imported;
	il->imported = 1;
	return ret;
}
