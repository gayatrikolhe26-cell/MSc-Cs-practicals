import scala.io.StdIn

object StringArraySearch {
  def main(args: Array[String]): Unit = {

    
    var arr = Array(
      "Scala Programming",
      "Java Programming",
      "Python Programming",
      "Scala Language",
      "C Programming"
    )

    println("Enter target string:")
    var target = StdIn.readLine()

    println("Elements containing '" + target + "':")

   
    for (str <- arr) {
      if (str.contains(target)) {
        println(str)
      }
    }
  }
}
