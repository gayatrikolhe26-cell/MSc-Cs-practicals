object CountUppercase {
  def main(args: Array[String]): Unit = {

    var str = "Scala Programming Language"

    var count = 0

    // Count uppercase letters
    for (ch <- str) {
      if (ch.isUpper) {
        count = count + 1
      }
    }

    
    var lower = str.toLowerCase

    println("Original String = " + str)
    println("Number of uppercase letters = " + count)
    println("Lowercase String = " + lower)
  }
}
