data {
  int<lower=0> N; 
  int<lower=0> n_eth; 
  int<lower=0> n_age; 
  vector[N] y;
  vector[N] x_centered;
  int eth[N];
  int age[N];
} 
transformed data {
  int<lower=0> n_eth_age;
  int eth_age[N];
  
  for (i in 1:N)
    eth_age[i] <- eth[i] * age[i];
  n_eth_age <- n_eth * n_age;
}
parameters {
  real<lower=0> sigma_y;
  real<lower=0> sigma_a;
  real<lower=0> sigma_b;
  real<lower=0> sigma_c;
  real mu_a;
  real mu_b;
  real mu_c;
  matrix[n_eth,2] eta_a;
  matrix[n_age,2] eta_b;
  matrix[n_eth_age,2] eta_c;
}
transformed parameters {
  vector[N] y_hat;
  matrix[n_eth,2] a;
  matrix[n_age,2] b;
  matrix[n_eth_age,2] c;

  a <- mu_a + sigma_a * eta_a;
  b <- mu_b + sigma_b * eta_b;
  c <- mu_c + sigma_c * eta_c;

  for (i in 1:N)
    y_hat[i] <- a[eth[i],1] + a[eth[i],2] * x_centered[i] + b[age[i],1] 
                + b[age[i],2] * x_centered[i] + c[eth_age[i],1] 
                + c[eth_age[i],2] * x_centered[i];
} 
model {
  mu_a ~ normal(0, 100);
  for (j in 1:n_eth)
    eta_a[j] ~ normal(0, 1);

  mu_b ~ normal(0, 100);
  for (j in 1:n_age)
    eta_b[j] ~ normal(0, 1);

  mu_c ~ normal(0, 100);
  for (j in 1:n_eth_age)
    eta_c[j] ~ normal(0, 1);

  y ~ normal(y_hat, sigma_y);
}