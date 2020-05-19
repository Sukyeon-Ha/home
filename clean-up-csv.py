#!/usr/bin/env python3

seq_info = dict()
f_csv = open('../data/2019nCoV_genomes.2020_04_14.csv', 'r')
f_csv.readline()
for line in f_csv:
    tokens = line.replace(' ', '_').strip().split(',')
    seq_id = tokens[0]

    collect_date = tokens[-1]
    if len(collect_date) == 7:
        collect_date += '-00'
    geo_location = tokens[4]
    geo_location = geo_location.replace('North_Carolina', 'NC')
    geo_location = geo_location.replace('Illinois', 'IL')
    geo_location = geo_location.replace('San_Francisco', 'CA-SF')
    geo_location = geo_location.replace('"', '')
    isolation_source = tokens[6]
    #print(geo_location)
    if geo_location not in seq_info:
        seq_info[geo_location] = dict()

    seq_info[geo_location][seq_id] = collect_date
f_csv.close()
#Accession,Release_Date,Species,Length,Geo_Location,Host,Isolation_Source,Collection_Date
#NC_045512,2020-01-13T00:00:00Z,Severe acute respiratory syndrome-related coronavirus,29903,China,Homo sapiens,,2019-12

#==> 2019nCoV_genomes.2020_04_14.fa <==
#>NC_045512 |Severe acute respiratory syndrome coronavirus 2 isolate Wuhan-Hu-1| complete genome
#ATTAAAGGTTTATACCTTCCCAGGTAACAAACCAACCAACTTTCGATCTCTTGTAGATCT

seq_list = dict()
f_fa = open('../data/2019nCoV_genomes.2020_04_14.fa', 'r')
for line in f_fa:
    if line.startswith('>'):
        tmp_h = line.strip().lstrip('>').split()[0]
        seq_list[tmp_h] = []
    else:
        seq_list[tmp_h].append(line.strip())
f_fa.close()

for tmp_loc in sorted(seq_info.keys()):
    if tmp_loc == '':
        continue
    if len(seq_info[tmp_loc]) < 3:
        continue

    for tmp_id, tmp_date in seq_info[tmp_loc].items():
        tmp_seq = ''.join(seq_list[tmp_id])
        print(">%s|%s|%s\n%s" % (tmp_id, tmp_loc.replace(':', '_'), tmp_date, tmp_seq))
