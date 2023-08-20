# PZB Remote Testing Unit

This Site shows my own creation to make my worklife and that of others easier.
This is my first GitHub Project and Iam still learning how to use it properly.

The PZB Remote Testing Unit uses two ESP32 Microcontrollers to establish a wireless communication between a Transmitter and Receiver Unit.

# What is it used for?

What is PZB?
PZB is a German train protection system which is also used in Austria, Slovenia, Croatia, Romania, Israel and Serbia.

How is PZB tested?
To test the PZB functionality we use a so called testmagnet which uses three different coils inside depending on which coil gets closed the train gets a different order on which it reacts

500Hz is a speed limiter which does not need acknowledgment by the train driver
1000Hz is also a speed limiter which is placed infront of signal that signals a halt, this one needs acknowledgment by the train driver if not done so he will get an emergency brake
2000Hz is the emergency stop which is not to be driven over and will trigger an emergency brake if done so.

Why do the coils have frequency?
PZB uses Passive tuned inductors inside a trainborne antenna on the right side of the cab which is in driving direction if the antenna is being driven over a trackside antenna the passive tuned inductor
with the same frequency is being influenced and the current inside that circuit gets lowered below a certain threshhold which the train protection system recognizes and acts accordingly.

Why do we need a Remote Testing Unit?
Normally we would use a wired remote with three buttons to test the funcionality of the train protection system but in some cases it is a real hassle for the people working on it
cables getting tangled, getting the cables inside and out of the cab and generally moving the testing equipment from one cab to the other.

# Which Systems can be tested?

The RTU can be used for normal LZB80/PZB90 Systems like the normal LZB80, LZB80E or EBICAB train protection systems found in nearly all german trains.

The testing for LZB80/LZB80E is fairly simple and requires only a test magnet and it can be tested normally.

The testing for EBICAB needs an Adapter Cable which is supplied with every RTU and the so called HDF-Tool which
simulates a track being driven on and uses the RTU as a Wi-Fi bridge between the HDF-Tool and the test magnet.

