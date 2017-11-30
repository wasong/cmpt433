import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

const Image = ({
  image,
}) => (
  <div>
    <img src={image} alt="webcam" />
  </div>
)

Image.propTypes = {
  image: PropTypes.string,
}

Image.defaultProps = {
  image: '',
}

export default Radium(Image)
