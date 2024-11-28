#!/bin/bash

first_argu=$1
first_call=first_call.txt

first_argu=${first_argu%/}

# First call
if [ ! -e $first_call ]; then
  touch first_call.txt

  if [ $# -lt 1 ]; then
    echo "Must include valid path" >&2
    rm -f first_call.txt
    exit
  fi

  if [ ! -d $first_argu ]; then
    echo "Must include valid path" >&2
    rm -f first_call.txt
    exit
  fi

  echo "Welcome to the Big Brother"
  echo $first_argu > the_path.txt

  ls -1 -p --group-directories-first $1 > first_file_and_folders.txt
  if [[ $# -gt 1 ]]; then
    for ((i = 2; i <= $#; i++)); do
      echo ${!i} >> the_arguments.txt
    done
  fi
fi

# Second call
arr_of_deleted_files=()
arr_of_add_files=()
arr_of_add_folders=()
arr_of_deleted_folders=()

if [ ! -e second_call.txt ]; then
	touch second_call.txt

# If there are more than one argument in the first call
elif [ -e the_arguments.txt ]; then
	argu_inside=false
	the_path=$(cat the_path.txt)
	ls -1 --group-directories-first -p $the_path > cur_inside.txt

# Array of the arguments after the first one
	argument=()
	while IFS= read -r line; do
		argument+=($line)
	done < the_arguments.txt

# Array of the content inside the first argument
	first_arr=()
	while IFS= read -r line; do
		first_arr+=($line)
	done < first_file_and_folders.txt

# Array of the current content
	cur_arr=()
	while IFS= read -r line; do
		cur_arr+=($line)
	done < cur_inside.txt

 
#check if somthing deleted from the arguments
	for old in "${first_arr[@]}"; do 
		if [[ ! " ${cur_arr[@]} " =~ "$old" ]]; then
			found_in_arguments=false
			for arg in "${argument[@]}"; do
				if [[ "$old" == "$arg" || "$old" == "$arg/" ]]; then
					found_in_arguments=true
					break
					fi
			done
			if [[ $found_in_arguments == true ]]; then
				str=$old
				lastchar=${str: -1}
				if [[ $lastchar == "/" ]]; then
					str=${str%?}
					str="${str}-deleted"
					if [[ ! " ${arr_of_deleted_folders[@]} " =~ " $str " ]]; then
						arr_of_deleted_folders+=("$str")
					fi
				else
					str="${str}-deleted"
					if [[ ! " ${arr_of_deleted_files[@]} " =~ " $str " ]]; then
						arr_of_deleted_files+=("$str")
					fi
				fi
			fi
		fi
	done

#check if somthing added from the arguments 
	for current in "${cur_arr[@]}"; do
		if [[ ! " ${first_arr[@]} " =~ "$current" ]]; then
			for arg_current in "${argument[@]}"; do
				if [[ "$current" == "$arg_current" || "$current" == "$arg_current/" ]]; then
					if [[ "$current" != "first_call.txt" 
						&& "$current" != "the_path.txt" 
						&& "$current" != "the_arguments.txt" 
						&& "$current" != "first_file_and_folders.txt"
						&& "$current" != "second_call.txt" 
						&& "$current" != "cur_inside.txt" ]]; then
						str=$current
						lastchar=${str: -1}
						if [[ $lastchar == "/" ]]; then
							str=${str%?}
							str="${str}-added"
						if [[ ! " ${arr_of_add_folders[@]} " =~ " $str " ]]; then
							arr_of_add_folders+=("$str")
						fi
						else
							str="${str}-added"
							if [[ ! " ${arr_of_add_files[@]} " =~ " $str " ]]; then
								arr_of_add_files+=("$str")
							fi
						fi
					fi
				fi
			done
		fi
	done
	
#printed by sort (arguments in the first call)
	arr_of_deleted_folders=($(printf '%s\n' "${arr_of_deleted_folders[@]}" | sort))
	for current in "${arr_of_deleted_folders[@]}"; do
		the_remove=${current#*-}
		file="${current%%-*}"
		if [ "$the_remove" == "deleted" ]; then
			>&2 echo "Folder deleted: $file"
		fi
	done
	
	arr_of_deleted_files=($(printf '%s\n' "${arr_of_deleted_files[@]}" | sort))
	for current in "${arr_of_deleted_files[@]}"; do
		the_remove=${current#*-}
		file="${current%%-*}"
		if [ "$the_remove" == "deleted" ]; then
			>&2 echo "File deleted: $file"
		fi
	done



	arr_of_add_folders=($(printf '%s\n' "${arr_of_add_folders[@]}" | sort))
	for current in "${arr_of_add_folders[@]}"; do
		the_remove=${current#*-}
		folder="${current%%-*}"
		if [ "$the_remove" == "added" ]; then
			echo "Folder added: $folder"
		fi
	done

	arr_of_add_files=($(printf '%s\n' "${arr_of_add_files[@]}" | sort))
	for current in "${arr_of_add_files[@]}"; do
		the_remove=${current#*-}
		file="${current%%-*}"
		if [ "$the_remove" == "added" ]; then
			echo "File added: $file"
		fi
	done

	cat cur_inside.txt > first_file_and_folders.txt



# If there isn't more than one argument in the first call
else
	the_path=$(cat the_path.txt)
	ls -1 --group-directories-first -p $the_path > cur_inside.txt

# Array of the content inside the first argument
	first_arr=()
	while IFS= read -r line; do
		first_arr+=($line)
	done < first_file_and_folders.txt

# Array of the current content
	cur_arr=()
	while IFS= read -r line; do
		cur_arr+=($line)
	done < cur_inside.txt

 
#check if somthing deleted 
	for old in "${first_arr[@]}"; do 
		if [[ ! " ${cur_arr[@]} " =~ "$old" ]]; then
				str=$old
				lastchar=${str: -1}
				if [[ $lastchar == "/" ]]; then
					str=${str%?}
					str="${str}-deleted"
					if [[ ! " ${arr_of_deleted_folders[@]} " =~ " $str " ]]; then
						arr_of_deleted_folders+=("$str")
					fi
				else
					str="${str}-deleted"
					if [[ ! " ${arr_of_deleted_files[@]} " =~ " $str " ]]; then
						arr_of_deleted_files+=("$str")
					fi
				fi
			fi
	done

#check if somthing added 
	for current in "${cur_arr[@]}"; do
		if [[ ! " ${first_arr[@]} " =~ "$current" ]]; then
			if [[ "$current" != "first_call.txt" 
					&& "$current" != "the_path.txt" 
					&& "$current" != "the_arguments.txt" 
					&& "$current" != "first_file_and_folders.txt"
					&& "$current" != "second_call.txt" 
					&& "$current" != "cur_inside.txt" ]]; then
					str=$current
					lastchar=${str: -1}
					if [[ $lastchar == "/" ]]; then
						str=${str%?}
						str="${str}-added"
					if [[ ! " ${arr_of_add_folders[@]} " =~ " $str " ]]; then
						arr_of_add_folders+=("$str")
					fi
					else
						str="${str}-added"
						if [[ ! " ${arr_of_add_files[@]} " =~ " $str " ]]; then
							arr_of_add_files+=("$str")
						fi
					fi
				fi
			fi
	done


#printed by sort 
	arr_of_deleted_folders=($(printf '%s\n' "${arr_of_deleted_folders[@]}" | sort))
	for current in "${arr_of_deleted_folders[@]}"; do
		the_remove=${current#*-}
		file="${current%%-*}"
		if [ "$the_remove" == "deleted" ]; then
			>&2 echo "Folder deleted: $file"
		fi
	done
	
	arr_of_deleted_files=($(printf '%s\n' "${arr_of_deleted_files[@]}" | sort))
	for current in "${arr_of_deleted_files[@]}"; do
		the_remove=${current#*-}
		file="${current%%-*}"
		if [ "$the_remove" == "deleted" ]; then
			>&2 echo "File deleted: $file"
		fi
	done



	arr_of_add_folders=($(printf '%s\n' "${arr_of_add_folders[@]}" | sort))
	for current in "${arr_of_add_folders[@]}"; do
		the_remove=${current#*-}
		folder="${current%%-*}"
		if [ "$the_remove" == "added" ]; then
			echo "Folder added: $folder"
		fi
	done

	arr_of_add_files=($(printf '%s\n' "${arr_of_add_files[@]}" | sort))
	for current in "${arr_of_add_files[@]}"; do
		the_remove=${current#*-}
		file="${current%%-*}"
		if [ "$the_remove" == "added" ]; then
			echo "File added: $file"
		fi
	done

	cat cur_inside.txt > first_file_and_folders.txt
fi