/*=========================================================================

  Program:   Insight Segmentation & Registration Toolkit
  Module:    itkMaskNeighborhoodOperatorImageFilter.h
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) Insight Software Consortium. All rights reserved.
  See ITKCopyright.txt or http://www.itk.org/HTML/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#ifndef __itkMaskNeighborhoodOperatorImageFilter_h
#define __itkMaskNeighborhoodOperatorImageFilter_h

#include "itkNeighborhoodOperatorImageFilter.h"

namespace itk
{
/** \class MaskNeighborhoodOperatorImageFilter
 * \brief Applies a single NeighborhoodOperator to an image,  processing only those pixels that are under a mask
 *
 * This filter caculates successive inner products between a single
 * NeighborhoodOperator and a NeighborhoodIterator, which is swept
 * across every pixel that is set in the input mask. If no mask is
 * given, this filter is equivalent to its superclass.
 *
 * \ingroup ImageFilters
 *
 * \sa Image
 * \sa Neighborhood
 * \sa NeighborhoodOperator
 * \sa NeighborhoodOperatorImageFilter
 * \sa NeighborhoodIterator
 */
template <class TInputImage, class TMaskImage, class TOutputImage, class TOperatorValueType=ITK_TYPENAME TOutputImage::PixelType>
class ITK_EXPORT MaskNeighborhoodOperatorImageFilter :
    public NeighborhoodOperatorImageFilter< TInputImage, TOutputImage, TOperatorValueType > 
{
public:
  /** Standard "Self" & Superclass typedef. */
  typedef MaskNeighborhoodOperatorImageFilter Self;
  typedef NeighborhoodOperatorImageFilter< TInputImage, TOutputImage, TOperatorValueType > Superclass;
  typedef SmartPointer<Self> Pointer;
  typedef SmartPointer<const Self> ConstPointer;

  /** Method for creation through the object factory. */
  itkNewMacro(Self);

  /** Run-time type information (and related methods). */
  itkTypeMacro(MaskNeighborhoodOperatorImageFilter, NeighborhoodOperatorImageFilter);
  
  /** Extract some information from the image types.  Dimensionality
   * of the two images is assumed to be the same. */
  typedef typename TOutputImage::PixelType         OutputPixelType;
  typedef typename TOutputImage::InternalPixelType OutputInternalPixelType;
  typedef typename  TInputImage::PixelType         InputPixelType;
  typedef typename  TInputImage::InternalPixelType InputInternalPixelType;
  typedef typename   TMaskImage::PixelType         MaskPixelType;
  typedef typename   TMaskImage::InternalPixelType MaskInternalPixelType;

  /** Extract some information from the image types.  Dimensionality
   * of the two images is assumed to be the same. */
  itkStaticConstMacro(ImageDimension, unsigned int,
                      TOutputImage::ImageDimension);
  
  /** Image typedef support. */
  typedef TInputImage  InputImageType;
  typedef TMaskImage   MaskImageType;
  typedef TOutputImage OutputImageType;
  typedef typename InputImageType::Pointer InputImagePointer;
  typedef typename MaskImageType::Pointer MaskImagePointer;
  
  /** Typedef for generic boundary condition pointer. */
  typedef ImageBoundaryCondition<OutputImageType> *
  ImageBoundaryConditionPointerType;

  /** Superclass typedefs. */
  typedef typename Superclass::OutputImageRegionType OutputImageRegionType;
  typedef typename Superclass::OperatorValueType         OperatorValueType;

  /** Neighborhood types */
  typedef typename Superclass::OutputNeighborhoodType OutputNeighborhoodType;

  /** Set the mask image. Using a mask is optional.  When a mask is
   * specified, the normalized correlation is only calculated for
   * those pixels under the mask. */
  void SetMaskImage( const TMaskImage* mask);

  /** Get the mask image. Using a mask is optional.  When a mask is
   * specified, the normalized correlation is only calculated for
   * those pixels under the mask. */
  const TMaskImage* GetMaskImage() const;

  /** Set the output value for the pixels that are not under the mask.
   * Defaults to zero.
   */
  itkSetMacro( DefaultValue, OutputPixelType );

  /** Get the output value for the pixels that are not under the
   * mask. */
  itkGetMacro( DefaultValue, OutputPixelType );
  
protected:
  MaskNeighborhoodOperatorImageFilter() : m_DefaultValue( NumericTraits<OutputPixelType>::Zero ){}
  virtual ~MaskNeighborhoodOperatorImageFilter() {}
  void PrintSelf(std::ostream& os, Indent indent) const;
    
  /** MaskNeighborhoodOperatorImageFilter needs to request enough of an
   * input image to account for template size.  The input requested
   * region is expanded by the radius of the template.  If the request
   * extends past the LargestPossibleRegion for the input, the request
   * is cropped by the LargestPossibleRegion. */
  void GenerateInputRequestedRegion() throw (InvalidRequestedRegionError);

  /** MaskNeighborhoodOperatorImageFilter can be implemented as a
   * multithreaded filter.  Therefore, this implementation provides a
   * ThreadedGenerateData() routine which is called for each
   * processing thread. The output image data is allocated
   * automatically by the superclass prior to calling
   * ThreadedGenerateData().  ThreadedGenerateData can only write to
   * the portion of the output image specified by the parameter
   * "outputRegionForThread"
   *
   * \sa ImageToImageFilter::ThreadedGenerateData(),
   *     ImageToImageFilter::GenerateData() */
  void ThreadedGenerateData(const OutputImageRegionType& outputRegionForThread,
                            int threadId );

private:
  MaskNeighborhoodOperatorImageFilter(const Self&); //purposely not implemented
  void operator=(const Self&); //purposely not implemented

  OutputPixelType m_DefaultValue;

};
  
} // end namespace itk

#ifndef ITK_MANUAL_INSTANTIATION
#include "itkMaskNeighborhoodOperatorImageFilter.txx"
#endif

#endif

