# This is the "Experiment 2"
loggers_per_node=2
volatile_pool_size=2
snapshot_pool_size=1
reducer_buffer_size=1
duration_micro=10000000
thread_per_node=12
numa_nodes=4
log_buffer_mb=128
machine_name="DL580"
machine_shortname="dl580"
fork_workers=true
null_log_device=true
high_priority=false # To set this to true, you must add "yourname - rtprio 99" to limits.conf

. run_ycsb_s_common.sh