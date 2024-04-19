#!/bin/bash

declare -A player_scores  # Declare an associative array to store scores for each player

i=1
while [ $i -le 10 ]
do
  echo $i
  # Execute the game and capture the scores for each player
  scores=$(./Game SterrySX5 Dummy Dummy Dummy -i default.cnf -o output/default-auto-$i.res -s "$i" 2>&1 | grep "score")

  # Store scores in the associative array
  while IFS= read -r score_line; do
    player=$(echo "$score_line" | awk '{print $1}')
    value=$(echo "$score_line" | awk '{print $2}')
    if [[ ! -z $value ]]; then
      player_scores[$player]+="$value "  # Accumulate scores for each player
    fi
  done <<< "$scores"

  ((++i))
done

# Calculate mean score for each player and display at the end
echo "Mean scores:"
for player in "${!player_scores[@]}"
do
  scores="${player_scores[$player]}"
  read -ra score_array <<< "$scores"
  total=0
  count=${#score_array[@]}

  # Check if there are scores for the player
  if [[ $count -gt 0 ]]; then
    # Calculate total score for the player
    for score in "${score_array[@]}"
    do
      total=$((total + score))
    done

    # Calculate mean score
    mean=$(awk "BEGIN {printf \"%.2f\", $total / $count}")
    echo "$player: $mean"
  else
    echo "$player: No scores available"
  fi
done

./test.sh > stats &
