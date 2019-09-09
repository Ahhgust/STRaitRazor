#!/usr/bin/env perl

use strict;
use warnings;

if (@ARGV < 2) {
    die "Gimme a labeled fastq file and the original!\n";
}

my %h;

open IN, $ARGV[0] or
    die "Doh!";

while(<IN>){
    chomp;
    $h{$_}=1; # read the header
    for (1..3) { # skip the rest
        $_ = <IN>;

    }

}


open IN, $ARGV[1] or
    die "Doh!";

my $printIt=0;

while (<IN>) {
    chomp;
    if (!exists $h{$_}) {
        print $_ , "\n";
        for (1..3) {
            $_ = <IN>;
            print $_ if defined $_;
        }
    } else {
        for (1..3) {
            $_ = <IN>;
        }
    }

}
close IN;


