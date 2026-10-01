import scala.io.StdIn

object VowelsConsonants {
  def main(args: Array[String]): Unit = {

    println("Enter a string:")
    var str = StdIn.readLine()

    var vowels = 0
    var consonants = 0

    // Convert string to lowercase
    var text = str.toLowerCase

    // Check each character
    for (ch <- text) {

      if (ch == 'a' || ch == 'e' || ch == 'i' ||
          ch == 'o' || ch == 'u') {

        vowels = vowels + 1

      } else if (ch >= 'a' && ch <= 'z') {

        consonants = consonants + 1
      }
    }

    println("Number of vowels = " + vowels)
    println("Number of consonants = " + consonants)
  }
}
