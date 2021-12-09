#  First Name      : Khasha
#  Last Name       : Dehnad
#  Id              : 12345
#  purpose         : running ANN on titanic

remove(list=ls())

filename<-file.choose()
Titanic<-  read.csv(filename)




### remove all the records with missing value

?na.omit()
Titanic2<-data.frame(lapply(na.omit(Titanic),as.numeric))

index<-sort(sample(nrow(Titanic2 ),round(.30*nrow( Titanic2))))
training<- Titanic2[-index,]
test<- Titanic2[index,]

index <- seq (1,nrow(Titanic2),by=5)
test<- Titanic2[index,]
training<-Titanic2[-index,]

#install.packages("neuralnet")
library("neuralnet")
?neuralnet()
class(training$Survived)
net_Titanic2<- neuralnet( Survived~Class+Age+Sex ,training, hidden=10, threshold=0.01)

#Plot the neural network
plot(net_Titanic2)

## test should have only the input colum
ann <-compute(net_Titanic2 , test[,-4])
ann$net.result 

ann_cat<-ifelse(ann$net.result <1.5,1,2)
length(ann_cat)

table(Actual=test$Survived,predition=ann_cat)

wrong<- (test$Survived!=ann_cat)
error_rate<-sum(wrong)/length(wrong)
error_rate