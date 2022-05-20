#' Company : Stevens
#' Project : HW2
#' Purpose : HW2
#' First Name : David
#' Last Name : Fu
#' CWID : 10471854
#' Date : October 1, 2021
#' 
#' 
#' ###### Homework 2 ####
#' 
rm(list=ls()) 
#'
#' 1)
cancerData=read.csv("/Users/d0f05lt/School/CS513/HW2/breast-cancer-wisconsin.csv", header=TRUE)
cancerData$F6 <- as.numeric(cancerData$F6)
#' I) Summarize
#' 
summary(cancerData)

#' II) Find Missing Value
#' 
cancerData[rowSums(is.na(cancerData)) > 0,]


#' III) Replace Missing Value with mean
#' 
meanF6 <- mean(cancerData$F6 , na.rm=TRUE)
cancerData$F6[is.na(cancerData$F6)] <- meanF6

#' IV) Displaying the frequency table of Class vs F6
#' 
table(cancerData$Class,cancerData$F6)

#' V) Displaying scatter plot of F1 to F6
#' 
pairs(~cancerData$F1+cancerData$F2+cancerData$F3+cancerData$F4+cancerData$F5+cancerData$F6)

#' VI) Show historgram box plot for F7 to F9
#' 
hist(cancerData$F7)
boxplot(cancerData$F7)

hist(cancerData$F8)
boxplot(cancerData$F8)

hist(cancerData$F9)
boxplot(cancerData$F9)

#' Delete all Object and Reload Data then remove all column with missing value
rm(list=ls())
cancerData=read.csv("/Users/d0f05lt/School/CS513/HW2/breast-cancer-wisconsin.csv", header=TRUE)

cancerData$F6 <- as.numeric(cancerData$F6)
cancerData <- cancerData[rowSums(is.na(cancerData)) == 0,]
