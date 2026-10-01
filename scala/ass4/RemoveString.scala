import scala.io.StdIn

object RemoveString {
  def main(args: Array[String]): Unit = {

    println("Enter first string:")
    var str1 = StdIn.readLine()

    println("Enter second string:")
    var str2 = StdIn.readLine()

   
    var result = str1.replace(str2, "")

    println("Original String = " + str1)
    println("String to remove = " + str2)
    println("Result = " + result)
  }
}
