namespace result {

template <typename T>
Result<T>::Result() : Result(errors::make("the result is uninitialized")) {}

template <typename T>
Result<T>::Result(const T& val) : data(val), data_is_err(false) {}

template <typename T>
Result<T>::Result(const errors::Error& err) : data(err), data_is_err(true) {}

template <typename T>
template <typename U>
Result<T>::operator Result<U>() const {
  if (data_is_err) return std::get<errors::Error>(data);
  return static_cast<U>(std::get<T>(data));
}

template <typename T>
template <typename U>
Result<U> Result<T>::as() const {
  if (data_is_err) return std::get<errors::Error>(data);
  return static_cast<U>(std::get<T>(data));
}

template <typename T>
const T& Result<T>::unwrap() const {
  if (data_is_err) throw errors::make("the result contains an error");
  return std::get<T>(data);
}

template <typename T>
const errors::Error& Result<T>::unwrap_err() const {
  if (!data_is_err) throw errors::make("the result contains a value");
  return std::get<errors::Error>(data);
}

}  // namespace result
