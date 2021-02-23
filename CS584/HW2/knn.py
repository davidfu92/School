import numpy as np

def cos_sim(vector_x, vector_y):

  return np.dot(vector_x, vector_y) / (np.linalg.norm(vector_x) * np.linalg.norm(vector_y))


def find_neighbors(data, test, num_neighbors):

  distances = []
  for train_row in data:
    dist = cos_sim(test, train_row)
    distances.append((train_row, dist))
  neighbors = []
  for i in range(num_neighbors):
    neighbors.append(distances[i][0])
  return neighbors


def predict_neighbors(data, test, num_neighbors):

  neighbors = find_neighbors(data, test, num_neighbors)
  prediction = max(set(neighbors), key=neighbors.count)
  return prediction


def k_nearest(train, test, num_neighbors):

  predictions = []
  for row in test:
    output = predict_neighbors(train, row, num_neighbors)
    predictions.append(output)
  return(predictions)


def test_knearest():
  words = np.load('saved_params_40000.npy')

  target = np.random.randint(len(words), size=10)

  result_index = []
  for target_index in target:
    target_vector = words[target_index, :]
    result = k_nearest(target_vector, words[target_index], 10)
    result_index.append(result)

  print(result_index)


if __name__ == "__main__":
  test_knearest()
