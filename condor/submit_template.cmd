universe=Vanilla
+DESIRED_Sites="T2_US_UCSD"
executable=/home/users/phchang/ditto/condor/executable.sh
arguments=ANALYSIS HADOOPDIR SAMPLEFILENAME JOBTAG NEVENTS
transfer_executable=True
transfer_input_files=INPUTFILES
transfer_output_files = ""
+Owner = undefined
+project_Name="cmssurfandturf"
log=/nfs-7/userdata/phchang/ditto_skimmed_babies/log/ANALYSIS_JOBTAG/SAMPLEFILENAME.log
output=/nfs-7/userdata/phchang/ditto_skimmed_babies/log/ANALYSIS_JOBTAG/SAMPLEFILENAME.out
error=/nfs-7/userdata/phchang/ditto_skimmed_babies/log/ANALYSIS_JOBTAG/SAMPLEFILENAME.err
notification=Never
should_transfer_files = YES
when_to_transfer_output = ON_EXIT
x509userproxy=/tmp/x509up_u31617
queue
