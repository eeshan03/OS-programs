#! /bin/bash

it=0
a=1
while [[ $op -lt 7 ]]
do
	echo enter the option
	echo "1.Creation"
	echo "2.Addition"
	echo "3.Display"
	echo "4.Search"
	echo "5.Delete"
	echo "6.Modify"
	echo "7.exit"
	echo "enter your choice:"
	read op
word="$op"
case "$word" in

"1")	
	if [ "$op" == "1" ]
		then
		echo "enter the name of the book"
		read db
		touch "$db"
	fi
;;

"2")
	if [ "$op" == "2" ]
		then
		echo "in which book do you want to add records"
		read db
		echo "enter the no of records:"
		read n
		
	while [ $it -lt $n ]
	do
		echo "enter id:"
		read id1
		echo "enter name:"
		read nm
		pa1="^[A-Za-z]"
	while [[ ! $add =~ $pa ]]
	do
		echo "enter valid address:"
		read add
	done
	  echo "enter address:"
        read add
        pa="^[A-Za-z0-9]"
        while [[ ! $add =~ $pa ]]
        do
                echo "enter valid address:"
                read add
        done
        #echo $add
        
        echo "enter phone no.:"
        read ph
        pat="^[0-9]{10}$"
        while [[ ! $ph =~ $pat ]]
        do
                echo "please enter phone number as XXXXXXXXXX:"
                read ph
        done
        #echo $ph

        echo "eter email:"
        read em
        patem="^[a-z0-9._%-+]+@[a-z]+\.[a-z]{2,4}$"
        while [[ ! $em =~ $patem ]]
        do
                echo "please enter valid email address"
                read em
        done
        #echo $em

        echo "$id1,$nm,$add,$ph,$em" >> "$db"

        it=`expr $it + 1`
        echo "$it record entered"
        done
        fi
;;

"3")
	if [ "$op" == "3" ]
		then
		echo "enter the name of the book from where data is to be displayed"
		read db
		cat $db
	fi
;;

"4")
        if [ "$op" == "4" ]
                then
                echo "enter name of database from where to search:"
                read db
                echo "enter email to be search:"
                read em1
                grep $em1 $db
                echo "record found"
                else
                echo "not found"
        fi
;;

"5")
        if [ "$op" == "5" ]
                then
                echo "enter name of database:"
                read db
                echo "enter id:"
                read id1
                echo "enter line no. u want to delete:"
                read linenumber

                for line in `grep -n "$id1" $db`
                do
                number=`echo "$line" | cut -c1`
                #echo $number
                if [ $number == $linenumber ]
                then
                lineRemove="${linenumber}d"
                sed -i -e "$lineRemove" $db
                echo "record removed"
                fi
                #echo
                cat $db
                done
        fi
;;

"6")
        if [ "$op" == "6" ]
                then
                echo "enter name of database:"
                read db
                echo "enter id:"
                read id1
                echo "enter line u want to modify:"
                read linenumber

                for line in `grep -n "$id1" "$db"`
                do
                number=`echo "$line" | cut -c1`

                if [ "$number" == "$linenumber" ]
                then
                echo "what would u like to change"
                echo "\"id,name,address,mobile,email\""
                read edit
                linechange="${linenumber}s"
                sed -i -e "$linechange/.*/$edit/" $db
                echo record edited   
                fi
                done
        fi
;;

"7")
	echo "bye"
;;
*) echo invalid input
esac
done
