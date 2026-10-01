import scala.io.StdIn

object RemoveCharacter {
  def main(args: Array[String]): Unit = {

    println("Enter a string:")
    var str = StdIn.readLine()

    println("Enter the position of character to remove:")
    var position = StdIn.readInt()

    // Check whether position is valid
    if (position >= 0 && position < str.length) {

      // Remove the character
      var newString = str.substring(0, position) +
                      str.substring(position + 1)

      println("Original String = " + str)
      println("String after removing character = " + newString)

    } else {
      println("Invalid position!")
      println("Valid positions are from 0 to " + (str.length - 1))
    }
  }
}
