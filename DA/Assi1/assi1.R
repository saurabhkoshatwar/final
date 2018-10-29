data = read.csv("Iris.csv")
data
dim(data)
print(ncol(data))

sapply(data, class)
levels(data$Species)

summary(data$Species)

apply(data[,2:5],2,min)
apply(data[,2:5],2,max)
apply(data[,2:5],2,mean)
apply(data[,2:5],2,range)
apply(data[,2:5],2,sd)
apply(data[,2:5],2,var)
apply(data[,2:5],2,quantile)



print(min(data$SepalLengthCm))
print(max(data$SepalLengthCm))
print(mean(data$SepalLengthCm))
print(range(data$SepalLengthCm))
print(sd(data$SepalLengthCm))
print(var(data$SepalLengthCm))
print(quantile(data$SepalLengthCm))

hist(data$SepalLengthCm)
hist(data$SepalWidthCm)
boxplot(data[,-1])

boxplot(data$SepalWidthCm~data$Species,data=data)

count=table(data$Species)
count
percent=count/nrow(data)
percent
pie(percent)
box()

