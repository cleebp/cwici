#!/usr/bin/perl

$line1 = "./cwici test1.wic > test1.out";
print "$line1\n";
system $line1;

$line2 = "diff -b -B test1.wic test1.out > test1.diffs";
print "$line2\n";
system $line2;
