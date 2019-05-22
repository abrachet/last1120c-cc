        .global regtab
        .data
        .type regtab, %object
        .size regtab, 8
regtab:
        .xword 0
        .global efftab
        .data
        .type efftab, %object
        .size efftab, 8
efftab:
        .xword 1
        .global cctab
        .data
        .type cctab, %object
        .size cctab, 8
cctab:
        .xword 2
        .global sptab
        .data
        .type sptab, %object
        .size sptab, 8
sptab:
        .xword 3
        .global symbuf
        .bss
        .type symbuf, %object
        .size symbuf, 32
symbuf:
        .zero 32
        .global pssiz
        .data
        .type pssiz, %object
        .size pssiz, 8
pssiz:
        .xword 8
        .global namsiz
        .data
        .type namsiz, %object
        .size namsiz, 8
namsiz:
        .xword 8
        .global nwps
        .data
        .type nwps, %object
        .size nwps, 8
nwps:
        .xword 4
        .global hshused
        .data
        .type hshused, %object
        .size hshused, 8
hshused:
        .xword 0
        .global hshsiz
        .data
        .type hshsiz, %object
        .size hshsiz, 8
hshsiz:
        .xword 100
        .global hshlen
        .data
        .type hshlen, %object
        .size hshlen, 8
hshlen:
        .xword 800
        .global hshtab
        .bss
        .type hshtab, %object
        .size hshtab, 6400
hshtab:
        .zero 6400
        .global space
        .data
        .type space, %object
        .size space, 8
space:
        .xword 0
        .global cp
        .data
        .type cp, %object
        .size cp, 8
cp:
        .xword 0
        .global cmsiz
        .data
        .type cmsiz, %object
        .size cmsiz, 8
cmsiz:
        .xword 40
        .global cmst
        .bss
        .type cmst, %object
        .size cmst, 320
cmst:
        .zero 320
        .global ctyp
        .data
        .type ctyp, %object
        .size ctyp, 8
ctyp:
        .xword 0
        .global isn
        .data
        .type isn, %object
        .size isn, 8
isn:
        .xword 1
        .global swsiz
        .data
        .type swsiz, %object
        .size swsiz, 8
swsiz:
        .xword 120
        .global swtab
        .bss
        .type swtab, %object
        .size swtab, 960
swtab:
        .zero 960
        .global swp
        .data
        .type swp, %object
        .size swp, 8
swp:
        .xword 0
        .global contlab
        .data
        .type contlab, %object
        .size contlab, 8
contlab:
        .xword 0
        .global brklab
        .data
        .type brklab, %object
        .size brklab, 8
brklab:
        .xword 0
        .global deflab
        .data
        .type deflab, %object
        .size deflab, 8
deflab:
        .xword 0
        .global nreg
        .data
        .type nreg, %object
        .size nreg, 8
nreg:
        .xword 4
