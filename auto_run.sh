for ((i=0; i < $1; i++)); do
  ./knapsack
  mv ga_result_raw_record.csv $2/ga_result_raw_record_${i}.csv
  mv ga_result_uni_record.csv $2/ga_result_uni_record_${i}.csv
  mv ga_result_graph.pdf $2/ga_result_graph_${i}.pdf
done
