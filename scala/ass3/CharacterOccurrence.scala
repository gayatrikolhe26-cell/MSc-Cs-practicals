import scala.io.StdIn

object CharacterOccurrence {
  def main(args: Array[String]): Unit = {

    println("Enter a string:")
    var str = StdIn.readLine()

    println("Enter a character:")
    var ch = StdIn.readChar()

    var count = 0

    // Count occurrences of the character
    for(c <- str) {
      if (c == ch) { 
        count = count + 1
      }
    }

    println("Character '" + ch + "' occurs " + count + " times.")
  }
}
