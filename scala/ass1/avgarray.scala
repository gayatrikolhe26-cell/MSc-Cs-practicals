object avgarray{
   def main(args: Array[String]): Unit = {
   val ar=Array(10, 10, 10, 10, 10)
   val l=ar.length
   var sum=0
   for(a<-ar){
      sum+=a
   }
   val avg=sum/l
   println(s"the avg is $avg")
  }
}




