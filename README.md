fastqSol2Phred
==============
## Introduction
Simple C++ program to convert a FASTQ file in Solexa 1.3+ quality offset (QUAL+64 encoding) to a FASTQ with Phred/Sanger offset (QUAL+33 encoding). The current version does not work for Solexa quality scores on the older log probability scale.

## Compilation
'make' or 'g++ main.cpp -O3 -Wall -o fastqSol2Phred'

## Usage

#### Testing quality conversion
fastqSol2Phred unittest

#### Converting FASTQ file
fastqSol2Phred input.fq output.fqs
