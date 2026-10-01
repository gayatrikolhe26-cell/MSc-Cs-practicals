import scala.io.StdIn

object DuplicateCharacters {
  def main(args: Array[String]): Unit = {

    println("Enter a string:")
    var str = StdIn.readLine()

    
    var text = str.toLowerCase

    println("Duplicate characters and their counts:")

   
    for (ch <- text.distinct) {

      var count = text.count(c => c == ch)

     
      if (count > 1) {
        println(ch + " = " + count)
      }
    }
  }
}
