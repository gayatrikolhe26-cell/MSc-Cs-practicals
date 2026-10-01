import scala.io.StdIn

object ReplaceSpace {
  def main(args: Array[String]): Unit = {

    println("Enter a string:")
    var str = StdIn.readLine()

    // Replace spaces with hyphens
    var newString = str.replace(' ', '-')

    println("Original String = " + str)
    println("Modified String = " + newString)
  }
}
