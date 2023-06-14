import tensorflow as tf
import numpy as np
from tensorflow import keras
import os
import matplotlib.pyplot as plt
from PIL import Image


def create_model():
    model = keras.models.Sequential([
        keras.layers.Flatten(input_shape=(28, 28)),
        keras.layers.Dense(128, activation="relu"),
        keras.layers.Dropout(0.5),
        keras.layers.Dense(10)
    ])

    model.compile(optimizer='adam',
                  loss=tf.losses.SparseCategoricalCrossentropy(from_logits=True),
                  metrics=['accuracy'])

    return model


def train_model(model, train_images, train_labels, test_images, test_labels, weights_file_name):
    checkpoint_path = "minst_model/" + weights_file_name

    callback = keras.callbacks.ModelCheckpoint(filepath=checkpoint_path,
                                               save_weights_only=True,
                                               verbose=1)

    history = model.fit(train_images,
                        train_labels,
                        epochs=10,
                        validation_data=(test_images, test_labels),
                        callbacks=[callback])

    acc = history.history['accuracy']
    val_acc = history.history['val_accuracy']

    loss = history.history['loss']
    val_loss = history.history['val_loss']

    epochs_range = range(10)

    plt.figure(figsize=(8, 8))
    plt.subplot(1, 2, 1)
    plt.plot(epochs_range, acc, label='Training Accuracy')
    plt.plot(epochs_range, val_acc, label='Validation Accuracy')
    plt.legend(loc='lower right')
    plt.title('Training and Validation Accuracy')

    plt.subplot(1, 2, 2)
    plt.plot(epochs_range, loss, label='Training Loss')
    plt.plot(epochs_range, val_loss, label='Validation Loss')
    plt.legend(loc='upper right')
    plt.title('Training and Validation Loss')
    plt.show()


def load_weights(model, weights_file_name):
    checkpoint_path = "minst_model/" + weights_file_name
    model.load_weights(checkpoint_path)


def load_photo(name):
    my_digit_name = "my_test_data/" + name
    my_digit = Image.open(my_digit_name)
    my_digit = np.asarray(my_digit)
    my_digit = my_digit / 255.0
    return my_digit


def load_my_data():
    arr = [load_photo("0.1.bmp"), load_photo("0.2.bmp"), load_photo("0.3.bmp"),
           load_photo("1.1.bmp"), load_photo("1.2.bmp"), load_photo("1.3.bmp"),
           load_photo("2.1.bmp"), load_photo("2.2.bmp"), load_photo("2.3.bmp"),
           load_photo("3.1.bmp"), load_photo("3.2.bmp"), load_photo("3.3.bmp"),
           load_photo("4.1.bmp"), load_photo("4.2.bmp"), load_photo("4.3.bmp"),
           load_photo("5.1.bmp"), load_photo("5.2.bmp"), load_photo("5.3.bmp"),
           load_photo("6.1.bmp"), load_photo("6.2.bmp"), load_photo("6.3.bmp"),
           load_photo("7.1.bmp"), load_photo("7.2.bmp"), load_photo("7.3.bmp"),
           load_photo("8.1.bmp"), load_photo("8.2.bmp"), load_photo("8.3.bmp"),
           load_photo("9.1.bmp"), load_photo("9.2.bmp"), load_photo("9.3.bmp")]

    labels = [0, 0, 0, 1, 1, 1, 2, 2, 2, 3, 3, 3, 4, 4, 4, 5, 5, 5, 6, 6, 6, 7, 7, 7, 8, 8, 8, 9, 9, 9]
    return np.asarray(arr), np.asarray(labels)


def create_labels():
    return ["Zero", "Jeden", "Dwa", "Trzy", "Cztery", "Piec", "Szesc", "Siedem", "Osiem", "Dziewiec"]


def main():
    digits = keras.datasets.mnist
    (train_digits, train_labels), (test_digits, test_labels) = digits.load_data()

    model = create_model()
    load_weights(model, "minst_model.ckpt")

    train_digits = train_digits / 255.0
    test_digits = test_digits / 255.0

    my_digits, my_labels = load_my_data()

    # train_model(model, train_digits, train_labels, test_digits, test_labels, "minst_model.ckpt")

    loss, acc = model.evaluate(test_digits, test_labels)
    print(f"Accuracy: {acc * 100:5.2f}")

    # my_digit_name = "my_test_data/7.1.bmp"
    # my_digit = Image.open(my_digit_name)
    # # my_digit = my_digit.resize((28, 28))
    # my_digit = np.asarray(my_digit)
    #
    # my_digit = my_digit / 255.0
    #
    # # plt.figure()
    # # plt.imshow(my_digit)
    # # plt.colorbar()
    # # plt.grid(False)
    # # plt.show()
    #
    # my_digit = (np.expand_dims(my_digit, 0))
    #
    # prediction = model.predict(my_digit)
    # score = tf.nn.softmax(prediction[0])
    # print(my_labels[np.argmax(score)])


if __name__ == '__main__':
    main()
