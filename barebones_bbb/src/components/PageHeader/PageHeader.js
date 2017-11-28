import React from 'react'
import PropTypes from 'prop-types'
import Radium from 'radium'

const styles = {
  root: {
    width: '100%',
    fontSize: 18,
  },
}

const PageHeader = ({ title }) => (
  <div style={styles.root}>{title}</div>
)

PageHeader.propTypes = {
  title: PropTypes.string,
}
PageHeader.defaultProps = {
  title: 'Node JS Application',
}

export default Radium(PageHeader)
