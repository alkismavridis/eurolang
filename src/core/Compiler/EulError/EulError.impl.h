EulError::EulError(EulErrorType type, const std::string& message) {
    this->type = type;
    this->message = message;
}

EulError::EulError() {
    this->message = "";
    this->type = EulErrorType::NO_ERROR;
}

void EulError::reset() {
    this->message.clear();
    this->type = EulErrorType::NO_ERROR;
}
