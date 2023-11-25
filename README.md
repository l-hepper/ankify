# ankify

![Screenshot title](https://github.com/l-hepper/ankify/blob/main/screenshots/2023-11-17_15-17.png)

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

**Review Mode**

![Screenshot of Review Mode](https://github.com/l-hepper/ankify/blob/main/screenshots/2023-11-17_15-16.png)

<pre>
ankify -r my_notes.txt
</pre>

This mode simply iterates over the collection of flashcards, the 'ENTER' key can be used to display the back of cards and move onto the next card, while a card counter keeps track of the cards remaining. This mode is recommended for casual review and learning.

**Prompt Mode**

![Screenshot of Review Mode](https://github.com/l-hepper/ankify/blob/main/screenshots/2023-11-17_15-16_1.png)

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

**Formatting Flashcard Notes for Import to Anki**

<pre>
ankify -a my_notes.txt
</pre>

Ankify began as a simple script to format text notes created in VIM to a format readily parsable by the spaced-repetition flashcard program Anki. In this mode, Ankify will take the .txt flashcards and insert a TAB into the first line - this tells Anki the characters used to parse the front and back of cards. TABs are then inserted throughout the textfile at the end of each question line, indicating to Anki the front of a card, the next line following the TAB is then determined to be the answer, indicating to Anki the back of a card.

The formatted .txt files will be output to the working directory as the original filename with '_for_anki' appended. So 'my_notes.txt' will become 'my_notes_for_anki.txt'. These 'for_anki' .txt files can then be imported to anki as a basic question and answer pair, eliminating the need to manually enter cards.

**Formatting Prose into Flashcard format**

<pre>
ankify -q my_notes.txt
</pre>

Ankify incorporates the gpt-3.5 API to take regular prose notes and generate flashcards which cover the text's content. These flashcards can be used by Ankify for its other functions. Passing in the below prose text about the Roman Empire will produce flashcards to test on the contents of the notes. These flashcards will be output to the working directory as the original filename + '_gptflashcards.txt'. So 'my_notes.txt' will become 'my_notes_gptflashcards.txt'.

**Prose Notes**
<pre>
The Roman Empire, one of the most influential civilizations in history, existed for over a millennium, from 27 BCE to 476 CE. Established by Augustus Caesar, the first Emperor of Rome, it encompassed vast territories, stretching from Britain in the north to Egypt in the south and spanning three continents. The empire reached its territorial zenith in 117 CE under Emperor Trajan, covering approximately 5 million square kilometers.

Rome's political structure evolved from a republic to an autocracy, with a series of emperors leading the state. Augustus, born Gaius Octavius, initiated the Pax Romana, a period of relative peace and stability that lasted for about two centuries. The Roman Empire was characterized by remarkable engineering feats, exemplified by the construction of the Colosseum in 80 CE and the extensive network of roads, such as the famous Appian Way. Rome's population peaked at around one million people, making it the largest city in the ancient world.

Despite its grandeur, internal strife and external pressures led to the eventual decline of the Roman Empire. Economic challenges, military conflicts, and political instability contributed to its fragmentation. The year 476 CE marks the traditional date for the fall of the Western Roman Empire, when the last Roman emperor, Romulus Augustulus, was deposed by the Germanic chieftain Odoacer. The Eastern Roman Empire, known as the Byzantine Empire, continued for nearly a thousand years until the fall of Constantinople in 1453.
</pre>

**GPT-3.5 Generated Flashcards**
<pre>
When did the Roman Empire exist?
27 BCE to 476 CE.

Who was the first Emperor of Rome?
Augustus Caesar.

What was the territorial extent of the Roman Empire at its zenith in 117 CE?
Approximately 5 million square kilometers.

What period of relative peace and stability was initiated by Augustus Caesar?
Pax Romana.

Under which emperor did the Roman Empire experience its territorial peak?
Emperor Trajan (117 CE).

What were some notable engineering feats of the Roman Empire?
Construction of the Colosseum (80 CE) and an extensive network of roads, including the Appian Way.

What was the population of Rome at its peak?
Around one million people.

What marked the traditional date for the fall of the Western Roman Empire?
476 CE.

Who was the last Roman emperor of the Western Roman Empire?
Romulus Augustulus.

What marked the continuation of the Eastern Roman Empire after the fall of the Western Roman Empire?
The Byzantine Empire, lasting until 1453.
</pre>

