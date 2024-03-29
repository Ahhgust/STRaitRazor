# STRait Razor 3.0

### Documentation

**Note on usage**

STRait Razor is a *pair*. It is the executable/binary (.exe on Windows) and it is the config file. <br>
The config file requires **optimization**. In general it will not work well if you try out a new chemistry unless you do things to make it work well! For example, the ForenSeq config file we supply is (not surprisingly) designed for the ForenSeq and nothing else.
We take care to evaluate the tradeoff between locus size and throughput (in general, larger loci give more information content, but less reads will give support to said content). If you try a different chemistry, that size/throughput tradeoff will be *different*, similarly, the rules for how an allele is deemed to be present may need to be changed. This is especially true if the reads are short and/or if you are not using a PCR-based assay.  <br><br>
If you want to evaluate STRait Razor on a different chemistry and need help getting started please feel free to reach out to us. 
<br><br>
It should also be stressed that the current implementation doesn't call genotypes; it simply reports which alleles (including stutter alleles) are apparent. Calling genotypes is a much harder problem (especially when mixtures are considered) and it is an area of active research. Please see [STRait Razor Online](http://www.unthsc.edu/straitrazor) (SRO) for semi-automated solutions.

### Quick starts
**Quick and dirty start** (no support for compressed files, not a very sustainable way to do research) <br>
Windows users:<br>
Make a directory.<br>
Download str8rzr. To do this, click on  "Clone or download" on this site, and select Download ZIP. <br>
Put str8rzr.exe, batchCstr8.bat, the appropriate config file (Forenseq.config), and all fastq files into this directory.<br>
Double-click on batchCstr8.bat<br>
(and if windows "protects you", say run anyways)<br>

This will make a directory that corresponds to each fastq file. The summarised data are in the allsequences.txt file, which is encoded in plain text (uncompressed).<br>
<br>
To make sense of these data, please use STRait Razor Online (SRO)

Online application

http://www.unthsc.edu/straitrazor

Executable

https://www.unthsc.edu/graduate-school-of-biomedical-sciences/laboratory-faculty-and-staff/strait-razor/

Source code

https://github.com/ExpectationsManaged/STRaitRazorOnline


# STRait Razor without SRO:

We recommend using SRO. For legacy support (and those who like to ignore recommendations), you may wish to read the following:

To make str8rzr work with compressed files, you'll need to follow the instructions below.

**Less quick, but much better start**<br>
Windows users:<br>
First, make a bin. Bin's are special directories that contain executable (typically binary) files. <br>
You can do this by making a folder called "bin" in your C: drive (or really, any place else you like, just replace <br>
the word C:\bin with whatever path you chose to use.). *be careful not to overwrite any other directory called "bin" when you do this!*<br> 
Make a bin by going to: This PC, double clicking on the C: drive, and typing ctrl+shift+n or by right-clicking over the whitespace, and selecting New->Folder<br>
Change the name of the directory from "New folder" to bin <br>
<br>
Second, download 7zip from here or elsewhere: http://www.7-zip.org/download.html <br>
Install the 7zip application.
Go to where it was installed (e.g., C:\Program Files\7-Zip), copy the 7z program (ctrl+c), and paste it (ctrl+v) into your bin (C:\bin) <br>
<br>
Third, modify your PATH. Your PATH has a bunch of directories in it that contain programs that you'd like to run. <br>
We're going to add your bin (C:\bin) to you path. Lots of sites on the internet will tell you how to do this. Here's a link to one.
https://www.howtogeek.com/118594/how-to-edit-your-system-path-for-easy-command-line-access/
<br>
Fourth:
Ensure that 7z was both installed and in your PATH. Open a command prompt (one way: click on the windows icon in the bottom left, and type cmd.exe). <br>
type: *7z* <br>
What should happen is you see a bunch of information about how to run 7zip.
If you see a command like: '7z' is not recognized as an internal or external command, ... <br>
this likely means you didn't configure your PATH correctly. It may also mean that 7zip failed to install (much less likely) <br>
<br>
Fifth: Make a directory for your config file. This file has the information needed to characterize your STR/SNPs.
I'd suggest:
C:\Analysis\Str8Configs <br>
(making directories as needed) <br><br>
Sixth:<br>
Download str8rzr. To do this, click on  "Clone or download" on this site, and select Download ZIP.
Open up the zipped folder, and copy/move str8rzr.exe into your bin (C:\bin).
Take the appropriate config file(s), and put that into your config folder (C:\Analysis\Str8Configs) <br>
As of this writing, there are two officially supported config files: Forenseq.config and Powerseq.config <br>
<br>Seventh:<br>
Run str8rzr!
Make a directory for doing analyses: Say, C:\Analysis\FOO
(replace the word FOO with whatever you like)
Put a bunch of fastq (.fq) files into FOO
Put the batch script (batchCstr8.bat, downloaded from github) into the same directory.
Edit the batch script: <br>Change line 5 from:
SET config="Forenseq.config"<br> 
to:<br>
SET config="C:\Analysis\Str8Configs\Forenseq.config"<br>

*double click on the batch script*

This will run str8rzr.exe on every fastq file in the current directory. The fastqs can be uncompressed (.fastq) or compressed by gzip (.fastq.gz). It makes one folder for each file. The allsequences.txt file has all of the summarised STR/SNP data for that particular individual.

<br>
<br>
This less quick start way is probably better than the quick and dirty (above). It allows for a single directory for your config files, which is helpful. Note that config files may change; you'll need to use your own version control system to handle these differences, and update your .bat file accordingly.<br>
I would recommend keeping a single (parental) .bat script, and then tweaking them as needed, and placing the batch script you used in the same directory as you did your research. <br>
Also note, if you want to do more analyses within the same directory, you may want to move your fastq files into a separate directory (otherwise they'll be analyzed twice, which is perhaps not what you want).
<br><br>

To make sense of these data, please use the Excel-based workbooks developed by Jonathan King!
Here's a link to a V3 compatible workbook. <br>
https://www.dropbox.com/scl/fi/nxzprapt6dlcxzxo1ng6w/STRait-Razor-v3-Analysis.xlsm?rlkey=f1lys2nvewgzji1vfill77equ&dl=1 <br>
And here's a link to the manual (originally designed for previous versions of strait razor, but it all translates to v3). <br>
https://www.unthsc.edu/graduate-school-of-biomedical-sciences/wp-content/uploads/sites/13/STRait-Razor-Analysis-Manual.pdf <br>


More detailed information on str8rzr!

### New features! 
The config files now support a single two-base IUPAC code per anchor sequence (e.g., R). Hopefully this will help w/ known SNPs in the anchors! <br>
The anchor sequences can now optionally be reported in the allsequences.txt files! (option -i for Including the anchors) <br>

<br>
#### known issues<br>
There's been one computer architecture (windows 7 + Xeon processor) that's caused some issues with the str8rzr.exe executable. In this case, str8rzr would occassionally crash, and I had to recompile it for that computer (and since then it's been fine). Please let me know if you experience problems-- especially crashes-- it'll let me further diagnose the exact problems therein.



str8rzr is written in C/C++ with multithreading support using the pthreads library. This new release couples a new search strategy (see algorithm) coupled with a complete redesign of the code-base used to identify short tandem repeats (STRs). This code base is (ostensibly) portable, and has been rigorously tested in Windows, Mac, and Unix environments, though the excel workbooks used to analyze the STRs only work with Microsoft Excel and are unlikely to function in your typical linux installation (but see Wine; https://www.winehq.org/). 

Pick the pre-compiled binary version of str8rzr that is appropriate to your operating system (i.e., str8rzr.exe for windows, str8rzr_osX for mac-- note rename this to str8rzr for everything to function correctly, str8rzr for everything else), and run it as:

     	str8rzr -c configFile fastqfile > allsequences.txt

To use multithreading (not default; using 8 processors in this example), type:

       str8rzr -p 8 -c configFile fastqfile > allsequences.txt

Note that on linux/mac systems, if . is not in your PATH you need to type: 

      ./str8rzr … 

instead of str8rzr. 

Code requirements:
The included source code
A c++ compiler (tested using g++)

Code niceties:	
The following unix utilities:

	zcat 
	bzip2
	grep
	7zip (not really a unix utility per se, but it's handy)

which allows str8rzr to operate on compressed gzip (with zcat) or bz2 (with bzip2) files a la:

      zcat file.fastq.gz | str8rzr -c configFile > allSequences.txt
      
or for Windows users:
	
      7z file.fastq.gz -so | str8rzr -c configFile > allSequences.txt

Otherwise str8rzr only operates on (uncompressed) fastq files. grep can be used to parse out particular markers (e.g., 

     grep -w vWR allsequences.txt > vWR.txt 

will give you all of the lines that contain the character string vWR in the allsequences.txt file, and the > redirects that to a file) from the allsequences.txt file.


### Configuration file format:

str8rzr needs to know, *a priori*, which STRs (or really, any locus) you’re looking for. To do this, one needs to describe the locus; specifically, str8 needs to know unique sequences before and after the STR, what sort of motif is expected in the str (e.g., GATA), and both the period (4 for GATA), and the offset (that is, the number of non-STR bases we are capturing). The period and the offset are used to convert the length of the haplotype between the markers into the number of repeats found (i.e., to map MPS data into capillary electrophoresis (CE) data). Below is an example of a config file:

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
str8rzr uses the following search strategy:<br>
It uses the anchors, and searches each read from the fastq file for the locations of anchors (previously called flanks), and their orientation and strand, as well as the location of all sequence motifs. Anchor-search is approximate, permitting a single substitution (no indels), while search for the motif is exact. It then looks at the config file (see below), and str8rzr extracts the sequence between anchors if (and only if): <br>
1.	they match in the correct orientation (forward then reverse, positive strand or reverse then forward on the negative strand), <br>
2.	if the proper motif is found within these anchors (note that motifs may overlap anchors). <br>
3.	anchors themselves are not allowed to overlap, and as such if an overlap is found, the first anchor found is kept and the second anchor is discarded.<br>
4.	if they are found in the proper quantity<br>
a.	That is, if not specified, if an anchor is found it should be found exactly one time.<br>
i.	The rule of 1 can be extended to n times, as specified in the configuration file.<br>
ii.	Allowing for n matches allows the extraction of duplicated loci, and when n > 1, the longest haplotype is selected<br>
Note that loci are allowed to overlap (thus permitting the extraction of SNPs from within the haplotype). Once a locus has been found within a read, the intervening haplotype is extracted. The haplotype itself is recorded, and the number of times it is observed. This recording includes whether or not the haplotype was found on the positive or negative strand (as defined by the config file).<br>
<br>

### Description of flags
    Running str8rzr with no arguments to see the flags/options. EG:
    
    str8rzr

or

	./str8rzr

if its not in your PATH

STRait Razor v3.0 supports the following flags: <br>
<br>

       -c configFile (This is REQUIRED). A configuration file (as described above.)
       -n (No reverse complementing-- str8rzr automically reverse complements haplotypes found on the negative strand to the positive strand. Really, to the same strand as specified in the config file)
       -v (Verbose ; this prints out some additional summary statistics that pertain to incomplete haplotype matches)
       -i (Include anchors ; includes the anchor sequences in the reported haplotypes)
       -a (Anchor Hamming distance. This is the (maximum) Hamming distance allowed between a substring of a read and the anchor sequence as to what constitutes a match. 1 is the default. Setting to 0 and 2 is allowed, but not recommended. being too strict (0) will cause allelic dropout in individuals with SNPs in the anchors, and setting it to 2 will take longer to build the trie, and cause false matches, and in turn cause reads to be dropped. e.g., if anchor should be present only once, setting this to two may (and will) cause reads to falsely "match" anchors to two locations, which in turn causes the intervenfging haplotype to be dropped.)
       -m (Motif Hamming distance. default=0, 1 is allowed. This hasn't been as thoroughly vetted as the -a flag, but setting this to 0 works well in practice).
       -p numProcessors (default=1. Can be any positive integer, but setting it equal to the number of cores on your system is probably a good idea. This turns on multiple threads)
       -t filTer (eg., autosomes, this filters the output to just that of the TYPE specified in the config file. This is acheived simply by only adding in the records that match that type from the config file into the data structures)
       -o filename (This redirects the output to a file)
       -f count (this removes haplotypes with less than *count* occurrences from the output. The vast majority of entries in the output of this program are "singletons"-- ie, haplotypes that occur once. This cleans that at up)


### Compiling

Ostensibly, you won't need to compile str8rzr from the sourcecode. But if you're really keen on trying, try the instructions below:

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
If you stuck with the default installation directory, then you need to add: C:\Program Files (x86)\mingw-w64\i686-6.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin to your PATH. To do this, click on the prompt and search for Environment Variable. Under system properties->advanced->environment variables, go to System variables, and click on Path (case insensitive spelling), and edit, and add the above path (C:\Program Files (x86)\mingw-w64\i686-6.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin) to your path. This is probably a good place to stash unix utilities as well (e.g., grep, head, tail).  As a reminder, your PATH is a set of directories that contain the executables (typically binaries) that are available for you to run. e.g., when you complete the above installation instructions, C:\Program Files (x86)\mingw-w64\i686-6.2.0-posix-dwarf-rt_v5-rev1\mingw32\bin will be in your PATH, and you can add str8rzr to that directory and it will work from any directory on your system.
 	
To get zcat and/or bzip2 (or any of a handful of unix utilities that have been ported to windows), use: 
<blockquote>https://sourceforge.net/projects/unxutils/</blockquote><br>
And add zcat, bzip2 and grep (and any other utility that catches your fancy. egrep anyone?) to a directory in your PATH (such as the one you just made!). 


Compiling the code 
Mac/linux:
Simply type:<br>
<blockquote>	make </blockquote>

Windows:
<blockquote>	mingw32-make </blockquote>
	
This command will make the str8rzr binary

Working with compressed files:
By example:
Gzipped files:
<blockquote> zcat example.fastq.gz | str8rzr -c configFile > allsequences.txt </blockquote>
Bz2 files:
<blockquote> bunzip2 -c example.fastq.bz2 | str8rzr -c configFile > allsequences.txt </blockquote>

(if this syntax fails, you’re probably on a windows system and you probably failed to install zcat/bunzip2. Type zcat --help or bunzip2 --help . If you see instructions on how to use these programs, that means that they’re installed correctly and the problem lies with str8rzr (so contact me, August). Otherwise, try and fix the installation.

### Algorithms for Approximate String matching: <br>
Previous build (v <= 2.6): <br>
The previous builds of str8rzr used the unix utility tre-agrep, which is an implementation of Gene Myer’s (Myers 1999) bitap algorithm (https://en.wikipedia.org/wiki/Bitap_algorithm). Bitap can be used to find inexact string matches under the Levenshtein distance function (ie, the unit edit distance; see https://en.wikipedia.org/wiki/Edit_distance). Bitap was applied to each flank for each read, so it scales according to the number of reads (R) * the number of anchors (A) * the longest anchor length m. For a constant edit distance, this strategy scales according to O(RAm). The default setting was to find matching substrings +/- any single substitution (but not to consider 1-base indels).



This build (v 3.?):
	The number of markers that one searches for is usually quite small (usually ~100), and the number of reads can be large (essentially unbounded. Str8 (v3.0) uses exact string matching algorithms (which are very fast) over every possible marker, as well as every single 1-base permutation of that marker (considering substitutions only). Because the number of markers is small, the computation time/space to do this is quite small. The basic search strategy is then to look at every possible suffix of each read, and then look for a matching entry in the trie described below. e.g., With this approach first the whole read would be searched, then the whole read save the first base, and then save the 1st and 2nd base, and so on. A match would then be reported if the first m bases matched, where m is the length of the marker whose prefix matches. (I do abuse syntax with m, m may vary across markers, but I refer to it as a singular value. It’s not, and my apologies for that, but note that this abuse doesn’t change the asymptotic analysis).
STRait v3.0 uses a trie (https://en.wikipedia.org/wiki/Trie) composed over every anchor (marker), and over every single-base substitution of that marker. Tries can be searched in time O(m) for a marker of length m, regardless of the number of markers in the trie. Thus every single marker can be searched for simultaneously, leading to a search time of O(nm) (where n is the number of bases being searched). If there are l flanks of length m, you can build the trie in O(l*m) time and space (note that if we’re adding all single-base substitutions to our markers the number of markers in the trie is m2).
	

References:
Myers, G. (1999) "A fast bit-vector algorithm for approximate string matching based on dynamic programming." Journal of the ACM 46 (3), 395–415.


