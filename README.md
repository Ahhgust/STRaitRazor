# STRaitRazor

Str8rzr 3.0 Documentation


Getting started:
Str8rzr 3.0 is written in C/C++ with multithreading support using the pthreads library. This new release couples a new search strategy (see algorithm) coupled with a complete redesign of the code-base used to identify short tandem repeats (STRs). This code base is (ostensibly) portable, and has been rigorously tested in Windows, Mac, and Unix environments, though the excel workbooks used to analyze the STRs only work with Microsoft Excel and are unlikely to function in your typical linux installation (but see Wine; https://www.winehq.org/). 

Quick start:
Pick the pre-compiled binary version of cstr8 that is appropriate to your operating system (i.e., cstr8.exe for windows, cstr8_osX for mac-- note rename this to cstr8 for everything to function correctly, cstr8 for everything else), and run it as:

     	cstr8 -c configFile fastqfile > allsequences.txt

To use multithreading (not default; using 8 processors in this example), type:

       cstr8 -p 8 -c configFile fastqfile > allsequences.txt

Note that on linux/mac systems, if . is not in your PATH you need to type: 

      ./cstr8 … 

instead of cstr8. 

Code requirements:
The included source code
A c++ compiler (tested using g++)

Code niceties:	
The following unix utilities:

	zcat 
	bzip2
	grep
	7zip (not really a unix utility per se, but it's handy)

which allows cstr8 to operate on compressed gzip (with zcat) or bz2 (with bzip2) files a la:

      zcat file.fastq.gz | cstr8 -c configFile > allSequences.txt
      
or for Windows users:
	
      7z file.fastq.gz -so | cstr8 -c configFile > allSequences.txt

Otherwise cstr8 only operates on (uncompressed) fastq files. grep can be used to parse out particular markers (e.g., 

     grep -w vWR allsequences.txt > vWR.txt 

will give you all of the lines that contain the character string vWR in the allsequences.txt file, and the > redirects that to a file) from the allsequences.txt file.


 
Mac users:
	If you’re using a mac you’re (essentially) using a linux system (congrats!). If you don’t have g++ installed, you can either install xcode (this is a comprehensive solution and installs many coding niceties, though it requires you to register with your corporate overlords), via:

	https://developer.apple.com/xcode/ide/
	(note this is a ~4.7G installation)

If you just want the gnu compiler, you can also try:

	https://github.com/kennethreitz/osx-gcc-installer
	(~1/10 the size, though I have not personally tested it)

Linux users:
	If you’re using linux you probably know what you’re doing. As a reminder, your system (most likely) already has g++, and if not you can use apt-get or yum (depending on your package manager a la): 

<blockquote>sudo apt-get install g++ </blockquote>
or
<blockquote>sudo yum install gcc-c++ </blockquote>

(You will of course need admin privileges to do this!)

Windows users:
	I’ve included binaries which should run on windows without further work on your part. That being said I’ve only tested them on (64-bit) windows10 and windows7. If you wish to recompile them you need MinGW-w64, which is available here:
	https://sourceforge.net/projects/mingw-w64
Click on the green download button. Run the downloaded program, keeping the default settings as-is.
After you install mingw-w64, make sure you set up your PATH environmental variable! 
If you stuck with the default installation directory, then you need to add: C:\Program Files (x86)\mingw-w64\i686-6.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin to your PATH. To do this, click on the prompt and search for Environment Variable. Under system properties->advanced->environment variables, go to System variables, and click on Path (case insensitive spelling), and edit, and add the above path (C:\Program Files (x86)\mingw-w64\i686-6.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin) to your path. This is probably a good place to stash unix utilities as well (e.g., grep, head, tail).  As a reminder, your PATH is a set of directories that contain the executables (typically binaries) that are available for you to run. e.g., when you complete the above installation instructions, C:\Program Files (x86)\mingw-w64\i686-6.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin will be in your PATH, and you can add cstr8 to that directory and it will work from any directory on your system.
 	
To get zcat and/or bzip2 (or any of a handful of unix utilities that have been ported to windows), use: 
<blockquote>https://sourceforge.net/projects/unxutils/</blockquote><br>
And add zcat, bzip2 and grep (and any other utility that catches your fancy. egrep anyone?) to a directory in your PATH (such as the one you just made!). 


Compiling the code 
Mac/linux:
Simply type:<br>
<blockquote>	make </blockquote>

Windows:
<blockquote>	mingw32-make </blockquote>
	
This command will make the cstr8 binary

Working with compressed files:
By example:
Gzipped files:
<blockquote> zcat example.fastq.gz | cstr8 -c configFile > allsequences.txt </blockquote>
Bz2 files:
<blockquote> bunzip2 -c example.fastq.bz2 | cstr8 -c configFile > allsequences.txt </blockquote>

(if this syntax fails, you’re probably on a windows system and you probably failed to install zcat/bunzip2. Type zcat --help or bunzip2 --help . If you see instructions on how to use these programs, that means that they’re installed correctly and the problem lies with cstr8 (so contact me, August). Otherwise, try and fix the installation.


Configuration file format:

cstr8 needs to know, *a priori*, which STRs (or really, any locus) you’re looking for. To do this, one needs to describe the locus; specifically, str8 needs to know unique sequences before and after the STR, what sort of motif is expected in the str (e.g., GATA), and both the period (4 for GATA), and the offset (that is, the number of non-STR bases we are capturing). The period and the offset are used to convert the length of the haplotype between the markers into the number of repeats found (i.e., to map MPS data into capillary electrophoresis (CE) data). Below is an example of a config file:

|#Marker Name	| Type |	5' Anchor             |  3' Anchor      | Motif         |	Period	| Offset| 
| :---------: | :--: | :---------------------:  | :-------------: | :-----------: | :-----: | :---: | 
|CSF1PO	      | A    | GTAACTGCCTTCATAGATAG	  | TACTTAGAACAG    | AGATAGATAGAT  | 4	|  20| 
|D10S1248	    | A	   | GTCACAAACATATTAATGAA	  | GTTCCTTTAATA    | GGAAGGAAGGAA  | 4	| 41| 
|DXS10074	    | X	   | CTACTGCCCCACCTTTATTG	  | TCTGAGGGGCAC    | AAGAAAGAAAGA | 4	| 101| 
|DYS389I	    | Y	   | TACTTCTGTATCCAACTCTC	  | TCCCTCCCTCTA    | TCTATCTATCTA 	| 4 | 18| 
|DYS389II	    | Y	   | TACTTCTGTATCCAACTCTC,2	| TCCCTCCCTCTA    | TCTATCTATCTA | 4 | 70| 

The format is (by column) (lines beginning with a # are ignored):<br>
1.	Markers have a name<br>
2.	A type (user specified; in the example it specifies autosomal, or X or Y chromosome).<br>
3.	5’ Anchor sequences (assumedly on the positive strand)<br>
4.	3’ Anchor sequence (assumedly on the positive strand)<br>
5.	A motif (searched for using exact or approximate string search)<br>
6.	A period (e.g., 4 for a 4-base repeat)<br>
7.	And an offset (the number of bases in the haplotype that are not in the STR)<br>
Note that for the anchor, a quantification (see DYS389II) can be used on the flanks. This means that this flank should be present exactly twice in the above example. Further, in the case that the read is on the positive strand, both anchors should precede the 3’ anchor, and these anchors should be found exactly 2 times for the 5’ anchor and 1 time for the 3’ anchor. <br><br>


Algorithm description:<br>
cstr8 uses the following search strategy:<br>
It uses the anchors, and searches each read from the fastq file for the locations of anchors (previously called flanks), and their orientation and strand, as well as the location of all sequence motifs. Anchor-search is approximate, permitting a single substitution (no indels), while search for the motif is exact. It then looks at the config file (see below), and cstr8 extracts the sequence between anchors if (and only if): <br>
1.	they match in the correct orientation (forward then reverse, positive strand or reverse then forward on the negative strand), <br>
2.	if the proper motif is found within these anchors (note that motifs may overlap anchors). <br>
3.	anchors themselves are not allowed to overlap, and as such if an overlap is found, the first anchor found is kept and the second anchor is discarded.<br>
4.	if they are found in the proper quantity<br>
a.	That is, if not specified, if an anchor is found it should be found exactly one time.<br>
i.	The rule of 1 can be extended to n times, as specified in the configuration file.<br>
ii.	Allowing for n matches allows the extraction of duplicated loci, and when n > 1, the longest haplotype is selected<br>
Note that loci are allowed to overlap (thus permitting the extraction of SNPs from within the haplotype). Once a locus has been found within a read, the intervening haplotype is extracted. The haplotype itself is recorded, and the number of times it is observed. This recording includes whether or not the haplotype was found on the positive or negative strand (as defined by the config file).<br>
<br>

Algorithms for Approximate String matching: <br>
Previous build (v <= 2.6): <br>
The previous builds of cstr8 used the unix utility tre-agrep, which is an implementation of Gene Myer’s (Myers 1999) bitap algorithm (https://en.wikipedia.org/wiki/Bitap_algorithm). Bitap can be used to find inexact string matches under the Levenshtein distance function (ie, the unit edit distance; see https://en.wikipedia.org/wiki/Edit_distance). Bitap was applied to each flank for each read, so it scales according to the number of reads (R) * the number of anchors (A) * the longest anchor length m. For a constant edit distance, this strategy scales according to O(RAm). The default setting was to find matching substrings +/- any single substitution (but not to consider 1-base indels).



This build (v 3.?):
	The number of markers that one searches for is usually quite small (usually ~100), and the number of reads can be large (essentially unbounded. Str8 (v3.0) uses exact string matching algorithms (which are very fast) over every possible marker, as well as every single 1-base permutation of that marker (considering substitutions only). Because the number of markers is small, the computation time/space to do this is quite small. The basic search strategy is then to look at every possible suffix of each read, and then look for a matching entry in the trie described below. e.g., With this approach first the whole read would be searched, then the whole read save the first base, and then save the 1st and 2nd base, and so on. A match would then be reported if the first m bases matched, where m is the length of the marker whose prefix matches. (I do abuse syntax with m, m may vary across markers, but I refer to it as a singular value. It’s not, and my apologies for that, but note that this abuse doesn’t change the asymptotic analysis).
STRait v3.0 uses a trie (https://en.wikipedia.org/wiki/Trie) composed over every anchor (marker), and over every single-base substitution of that marker. Tries can be searched in time O(m) for a marker of length m, regardless of the number of markers in the trie. Thus every single marker can be searched for simultaneously, leading to a search time of O(nm) (where n is the number of bases being searched). If there are l flanks of length m, you can build the trie in O(l*m) time and space (note that if we’re adding all single-base substitutions to our markers the number of markers in the trie is m2).
	

References:
Myers, G. (1999) "A fast bit-vector algorithm for approximate string matching based on dynamic programming." Journal of the ACM 46 (3), 395–415.


