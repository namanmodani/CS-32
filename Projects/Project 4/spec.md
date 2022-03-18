CS 32 Project 4, Winter 2022

Winter 2022 CS 32

Programming Assignment 4  
Unhinged
-----------------------------------

**Due 11:00 PM Thursday, March 10 Tuesday, March 15**  

The [Project 4 specification document](spec.pdf) has been posted. The posted [provided.zip](provided.zip) contains the four files pp. 2-3 say we will provide you.

If you log in to cs32.seas.ucla.edu, you can run a sample executable built with g32fast that uses the big members.txt and translator.txt files we gave you. The command is

	 /usr/local/cs/bin/samplep4

(It uses the big files /usr/local/cs/share/cs32w22p4/members.txt and /usr/local/cs/share/cs32w22p4/translator.txt.)

Update:
-------

3/7 5:30 pm: Clarification to MatchMaker::IdentifyRankedMatches: If the threshold is 0 or negative, although the returned vector must contain members with 1 or more matches, it is your choice whether or not it also contains members with 0 matches.