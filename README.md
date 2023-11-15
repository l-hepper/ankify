# ankify
CLI Tool for managing  and processing notes - includes modes for learning/review, self-testing(including an 'overkill' mode') and functionality to format the notes ready for import into Anki. This tool can utilise the gpt-3.5 API also to format regular prose notes into flashcard format suitable for Ankify.

# installation

# .txt file format

Ankify is intended for use with .txt files consisting of question and answer pairs to construct flashcards. These text files should be formatted as follows, with each side of the card contained on a single line. Blank lines can separate each of the cards and these will be ignored by ankify.

<pre>
Front of first card
Back of first card

Front of second card
Back of second card

Front of third card
Back of third card
</pre>

A 'real' example follows:

<pre>
What does it mean to say that arrays are stored 'contiguously' in memory? 
This means that the blocks of data are all adjacent to each other in memory. If an element of 4 bytes is stored at location '1000', then the next element starts at location 1004

To what two files in Linux do programs send their outputs?
stdout and stderr

What does an HTTP status code of 401 indicate?
HTTP status code 401 indicates "Unauthorized." - valid credentials have not been included in the 'Authorization' header
</pre>

N.B. Ankify uses TABS or '\t' to format notes for import into Anki, it is recommended NOT to have tabs in your notes if you intend to use this formatting feature.

# usage
<pre>
ankify  \[option]  \[filename.txt]
</pre>
To use Ankify type the 'ankify' command followed by the appropriate flag for the mode you want to run Ankify in, finally followed by the filename you are passing in to Ankify.

e.g. 

<pre>
ankify -r my_notes.txt
</pre>

A description of the modes follows:

**Review Mode**

<pre>
ankify -r my_notes.txt
</pre>

This mode simply iterates over the collection of flashcards, the 'ENTER' key can be used to display the back of cards and move onto the next card, while a card counter keeps track of the cards remaining. This mode is recommended for casual review and learning.

**Prompt Mode**

<pre>
ankify -p my_notes.txt
</pre>

This mode iterates over the collection of flashcards, requiring the user to input the correct answer for each card, i.e., Ankify will present the front of each card, and the user must enter the 'back' of the card precisely as it appears on the card. Prompt Mode is case sensitive as many topics require case sensitive information such as commands and programming syntax. This mode is not recommended for complex information and is best suited to small, atomic cards. A counter keeps track of the cards remaining, along with a counter for the number of correct and incorrect answers.

**Overkill Mode**

<pre>
ankify -x my_notes.txt
</pre>

N.B. not recommended for regular study.

A variation of Prompt Mode - overkill mode begins with a pool of 2 cards. These 2 cards must be answered correctly to increase the pool to 3. These 3 cards must then be answered correctly to increase the pool to 4, these 4 cards must then be answered correctly to increase the pool to 5. This mode successfully completes once all of the cards are in the pool and answered correctly in a row. If at any point an incorrect answer is provided - the entire process begins again from a pool size of 2. 

TIP: this mode can be used with small, atomic cards, such as testing knowledge of CLI commands. Ensure that no typos are in your answer before submitting to avoid frustration.

