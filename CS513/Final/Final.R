#' Company : Stevens
#' Project : Final
#' Purpose : Final
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : December 15, 2021
#' 
#' 
#' ###### Final ####
#' 
rm(list=ls())
set.seed(513)

## Problem 3
file<-file.choose()
factorData<- read.csv(file)

index<-sort(sample(nrow( factorData),round(.30*nrow(factorData ))))
training<- factorData[-index,]
test<- factorData[index,]

library("kknn")

predict_k1 <- kknn(formula= Z~., training[,c(-1)] , test[,c(-1)], k=2,kernel ="rectangular"  )

fit <- fitted(predict_k1)
table(test$Z,fit)

wrong<- ( test$Z!=fit)
rate<-sum(wrong)/length(wrong)
rate
## Problem 4

bc_dist<-dist(factorData[,c(-1,-2)])
hclust_resutls<-hclust(bc_dist )
plot(hclust_resutls)
hclust_2<-cutree(hclust_resutls,2)
table(Cluster=hclust_2,Actual=factorData[,2])

kmeans_2<- kmeans(factorData[,c(-1,-2)],2,nstart = 10)
kmeans_2$cluster
table(kmeans_2$cluster,Actual=factorData[,2] )


## Problem 5
summary(factorData)


mmnorm2 <-function(x)
{z<-((x-min(x))/(max(x)-min(x)))
return(z)                              
}

myvector<-1:20
mmnorm2(myvector)

library("neuralnet")

net  <- neuralnet( Z~ X+Y, training, hidden=1, threshold=0.01)




#Plot the neural network
plot(net)

result <-compute(net, test[,c(-1,-2)])
ANN=as.numeric(result$net.result)


ANN_cat<-ifelse(ANN<.4,.7,.4)

table(Actual=test$Z,ANN_cat)

wrong<- ( test$Z!=ANN_cat)
rate<-sum(wrong)/length(wrong)
rate
