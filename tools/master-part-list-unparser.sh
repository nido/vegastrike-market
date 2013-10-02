cat /usr/share/vegastrike/master_part_list.csv | sed "s/^\"\([^\"]\+\)\",\"\([^\"]\+\)\",\([0-9]\+\),\([0-9\.]\+\),\([0-9\.]\+\),\"@\([^@]\+\)@\([^\"]\+\)\"$/<CargoType name=\"\1\" catagory=\"\2\" mass=\"\4\" volume=\"\5\" price=\"\3\" \/>/g" | grep -v "^$" | grep -v ",,,,,"  | grep -v "starships" | grep -v "upgrades" | grep -v Passengers | grep -v Junk

