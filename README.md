# Similar_document_detector


This program was made by doing the calculation of a Jaccard Similarity(Interseccion/Union) of two texts, and then applying a second test using Minhash & LSH algorithms. It chunks the information of the two documents into chunks of words, oversized chunks will result into a slower execution (you can vary its size in the proper define in the code). It compares one document to all the others.

How TO EXECUTE IT:
- make the script executable by typing "chmod 755 open.sh" in the shell
- type in the file "comparables" all the files you want to compare, separed by spaces/tabs/endlines.
- type "./open.sh" so that the script performs the execution sorcery
- results will be in "resultat"


About the results:
The program will calculate the similarity between the first document and the rest. First column is the name of the paper, second is the Jaccard similarity between documents, the rest of columns are the different hash functions and its colisions between documents, a higher number of colisions implies a higher likelihood of them being copies.

The point of calculating so many similarities between 1 document of all the others it's efficiency, since if we see two programs that are rather similar in their diferences with document 1, then they are likely to be copies and should be tested between themselves.
