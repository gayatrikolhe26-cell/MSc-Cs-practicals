import scala.io.StdIn

object PalindromeCheck {
  def main(args: Array[String]): Unit = {

    println("Enter a string:")
    var str = StdIn.readLine()

    // Convert to lowercase
    var text = str.toLowerCase

    // Reverse the string
    var reverse = text.reverse

    // Pattern matching
    text match {

      case x if x == reverse =>//guard
        println("The string is a palindrome.")

      case _ =>
        println("The string is not a palindrome.")
    }
  }
}
