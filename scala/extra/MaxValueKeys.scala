object MaxValueKeys {

  def main(args: Array[String]): Unit = {
    val colors = Map(
      "Red" -> 1,
      "Green" -> 4,
      "Blue" -> 3,
      "Orange" -> 4
    )
    println("Original map: " + colors)
    val maxValue = colors.values.max
    val maxKeys = colors.filter(x => x._2 == maxValue).keys.toSet
    println("The keys with the maximum value are: " + maxKeys)
  }
}
