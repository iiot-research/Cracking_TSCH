# cracking_TSCH
Codes and sample data for cracking TSCH channel hopping

Time-Synchronized Channel Hopping (TSCH) was adopted by many leading industrial WSAN standards to exploit frequency diversity. All devices in the network compute the channel hopping sequences by following a function. This function-based channel hopping used in TSCH simplifies thenetwork operations. However, the channel sequences generatedby TSCH present a strong pattern, which introduces a security vul-nerability to the network. We present how an attacker derives the channel hopping sequences without knowing any parameter of the function in the following paper:

Xia Cheng, Junyang Shi, and Mo. Sha, “Cracking the Channel Hopping Sequences in IEEE 802.15.4e-Based Industrial TSCH Networks,” in IoTDI, 2019


# A “trial-and-error” learning method

Under realistic traffic, a transmittermay skip some scheduled time slots at runtime, which breaks therepetition pattern. However, we find that the attacker is able to accomplish the cracking by employing a “trial-and-error” learning method, which traverses all possible values of the combined slotframe length and outputs the actual value or its multiple.

Sample of processed channel activities: ./channel_activities_sample.txt

TSUR data: ./TSUR_1.txt

Sample TUSR data for deriving Ns or its multiple: ./TSUR_2.txt

Sample TSUR data for validation: ./TSUR_3.txt

Codes of deriving Ns or its multiple: ./Ns-Derive.c   
1. Modify the path of the TSUR file
2. Comple: gcc -o Ns-Derive Ns-Derive.c
3. Run: ./Ns-Derive
